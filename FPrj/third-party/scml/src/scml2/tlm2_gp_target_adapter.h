/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_TLM2_GP_TARGET_ADPATER_H
#define SCML2_TLM2_GP_TARGET_ADPATER_H

#include <scml2/mappable_if.h>

#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <tlm.h>
#include <systemc>
#include <sysc/kernel/sc_dynamic_processes.h>
#include <string>

namespace scml2 {

template <unsigned int BUSWIDTH,
          int N = 1,
          sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND>
class tlm2_gp_target_adapter :
  public sc_core::sc_object,
  public tlm::tlm_fw_transport_if<>,
  public tlm::tlm_bw_direct_mem_if
{
public:
  typedef tlm::tlm_base_target_socket<BUSWIDTH,
                                      tlm::tlm_fw_transport_if<>,
                                      tlm::tlm_bw_transport_if<>,
                                      N,
                                      POL> socket_type;

public:
  tlm2_gp_target_adapter(const std::string& name, socket_type& s);
  virtual ~tlm2_gp_target_adapter();

  std::string get_name() const;

  void operator()(mappable_if& destination);

  virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                             tlm::tlm_phase& phase,
                                             sc_core::sc_time& t);
  virtual void b_transport(tlm::tlm_generic_payload& trans,
                           sc_core::sc_time& t);
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi& dmiData);
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

  virtual void invalidate_direct_mem_ptr(unsigned long long startRange,
                                         unsigned long long endRange);

protected:
  void nb2b_thread(tlm::tlm_generic_payload& trans, sc_core::sc_event* e);
  void check_destination() const;

protected:
  socket_type& mSocket;
  mappable_if* mDestination;
  bool mResponseInProgress;
  sc_core::sc_event mEndResponse;
  mutable logging::stream mInternalError;
  mutable logging::stream mError;
};

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
tlm2_gp_target_adapter(const std::string& name, socket_type& s) :
  sc_core::sc_object(name.c_str()),
  mSocket(s),
  mDestination(0),
  mResponseInProgress(false),
  mInternalError(this->name(), logging::severity::internal_error()),
  mError(this->name(), logging::severity::error())
{
  mSocket(*this);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
~tlm2_gp_target_adapter()
{
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
std::string
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
get_name() const
{
  return name();
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
operator()(mappable_if& destination)
{
  if (mDestination) {
    SCML2_LOG(mError) << "interface already bound to adapter" << std::endl;
  }
  mDestination = &destination;
  mDestination->register_bw_direct_mem_if(this);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
tlm::tlm_sync_enum
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
nb_transport_fw(tlm::tlm_generic_payload& trans,
                tlm::tlm_phase& phase,
                sc_core::sc_time& t)
{
  if (phase == tlm::BEGIN_REQ) {
    sc_core::sc_spawn_options opts;
    opts.dont_initialize();
    sc_core::sc_event *e = new sc_core::sc_event;
    opts.set_sensitivity(e);
    sc_core::sc_spawn(sc_bind(&tlm2_gp_target_adapter<BUSWIDTH, N, POL>::nb2b_thread,
                              this,
                              sc_ref(trans),
                              e),
                      sc_core::sc_gen_unique_name("nb2b_thread"),
                      &opts);
    e->notify(t);
    return tlm::TLM_ACCEPTED;

  } else if (phase == tlm::END_RESP) {
    mResponseInProgress = false;
    mEndResponse.notify(t);
    return tlm::TLM_COMPLETED;

  } else {
    return tlm::TLM_ACCEPTED;
  }
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
nb2b_thread(tlm::tlm_generic_payload& trans, sc_core::sc_event* e)
{
  sc_core::sc_time t = sc_core::SC_ZERO_TIME;

  // forward call
  check_destination();
  (mDestination->b_transport)(trans, t);

  sc_core::wait(t);

  // return path
  while (mResponseInProgress) {
    sc_core::wait(mEndResponse);
  }
  t = sc_core::SC_ZERO_TIME;
  tlm::tlm_phase phase = tlm::BEGIN_RESP;
  tlm::tlm_sync_enum result = mSocket->nb_transport_bw(trans, phase, t);
  if (result == tlm::TLM_COMPLETED ||
      (result == tlm::TLM_UPDATED && phase == tlm::END_RESP)) {
    // cleanup
    delete e;

  } else {
    mResponseInProgress = true;
  }
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
check_destination() const
{
  if (!mDestination) {
    SCML2_LOG(mError) << "no interface bound" << std::endl;
  }
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
b_transport(tlm::tlm_generic_payload& trans,
            sc_core::sc_time& t)
{
  check_destination();
  mDestination->b_transport(trans, t);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
bool
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                   tlm::tlm_dmi& dmiData)
{
  check_destination();
  return mDestination->get_direct_mem_ptr(trans, dmiData);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
unsigned int
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
transport_dbg(tlm::tlm_generic_payload& trans)
{
  check_destination();
  return mDestination->transport_dbg(trans);
}

template <unsigned int BUSWIDTH, int N, sc_core::sc_port_policy POL>
inline
void
tlm2_gp_target_adapter<BUSWIDTH, N, POL>::
invalidate_direct_mem_ptr(unsigned long long startRange,
                          unsigned long long endRange)
{
  mSocket->invalidate_direct_mem_ptr(startRange, endRange);
}

}

#endif

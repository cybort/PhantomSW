/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WORD_ACCESS_UNROLLER_H
#define SCML2_WORD_ACCESS_UNROLLER_H

#include <scml2/word_access_unroller_base.h>

namespace sc_core {
  class sc_time;
}

namespace tlm {
  class tlm_generic_payload;
}

namespace scml2 {

// Unroll (streaming) word accesses into one or more word access
// (with byte enables)
template <typename DT, typename ADAPTER>
class word_access_unroller : public word_access_unroller_base<DT>
{
public:
  word_access_unroller(ADAPTER adapter);

  void operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

private:
  virtual bool process_unrolled_access(DT& data,
                                       const DT& byteEnables,
                                       sc_core::sc_time& t);

private:
  ADAPTER mAdapter;
};

template <typename DT, typename ADAPTER>
inline
word_access_unroller<DT, ADAPTER>
create_word_access_unroller(ADAPTER adapter)
{
  return word_access_unroller<DT, ADAPTER>(adapter);
}

template <typename DT, typename ADAPTER>
inline
word_access_unroller<DT, ADAPTER>::
word_access_unroller(ADAPTER adapter) :
  mAdapter(adapter)
{
}

template <typename DT, typename ADAPTER>
inline
void
word_access_unroller<DT, ADAPTER>::
operator()(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
  this->unroll_to_word_access(trans, t);
}

template <typename DT, typename ADAPTER>
inline
bool
word_access_unroller<DT, ADAPTER>::
process_unrolled_access(DT& data,
                        const DT& byteEnables,
                        sc_core::sc_time& t)
{
  return mAdapter(data, byteEnables, t);
}

}

#endif

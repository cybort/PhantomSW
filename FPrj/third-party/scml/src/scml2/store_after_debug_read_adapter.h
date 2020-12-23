/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_STORE_AFTER_DEBUG_READ_ADAPTER_H
#define SCML2_STORE_AFTER_DEBUG_READ_ADAPTER_H

#include <scml2/reg.h>

#include <tlm.h>

namespace scml2 {

template <typename MEM, typename ADAPTER>
class store_after_debug_read_adapter
{
public:
  store_after_debug_read_adapter(ADAPTER f, MEM& m);

  unsigned int operator()(tlm::tlm_generic_payload& trans);

public:
  ADAPTER mAdapter;
  MEM& mMemObject;
};

template <typename MEM, typename ADAPTER>
inline
store_after_debug_read_adapter<MEM, ADAPTER>
create_store_after_debug_read_adapter(ADAPTER f, MEM& m)
{
  return store_after_debug_read_adapter<MEM, ADAPTER>(f, m);
}

template <typename MEM, typename ADAPTER>
inline
store_after_debug_read_adapter<MEM, ADAPTER>::
store_after_debug_read_adapter(ADAPTER f, MEM& m) :
  mAdapter(f),
  mMemObject(m)
{
}

template <typename MEM, typename ADAPTER>
inline
unsigned int
store_after_debug_read_adapter<MEM, ADAPTER>::
operator()(tlm::tlm_generic_payload& trans)
{
  unsigned int result = mAdapter(trans);
  if (trans.is_read() && result != 0) {
    mMemObject.put_debug(trans.get_address(),
                         trans.get_data_ptr(),
                         result);
  }
  return result;
}

}

#endif

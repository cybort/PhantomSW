/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_STORE_AFTER_DEBUG_READ_ADAPTER_H
#define SCML2_BITFIELD_STORE_AFTER_DEBUG_READ_ADAPTER_H

#include <scml2/bitfield.h>

namespace scml2 {

template <typename DT, typename ADAPTER>
class bitfield_store_after_debug_read_adapter
{
public:
  bitfield_store_after_debug_read_adapter(ADAPTER f, bitfield<DT>& b);

  bool operator()(DT& value, const DT& bitMask);

public:
  ADAPTER mAdapter;
  bitfield<DT>& mBitfield;
};

template <typename DT, typename ADAPTER>
inline
bitfield_store_after_debug_read_adapter<DT, ADAPTER>
create_bitfield_store_after_debug_read_adapter(ADAPTER f, bitfield<DT>& b)
{
  return bitfield_store_after_debug_read_adapter<DT, ADAPTER>(f, b);
}

template <typename DT, typename ADAPTER>
inline
bitfield_store_after_debug_read_adapter<DT, ADAPTER>::
bitfield_store_after_debug_read_adapter(ADAPTER f, bitfield<DT>& b) :
  mAdapter(f),
  mBitfield(b)
{
}

template <typename DT, typename ADAPTER>
inline
bool
bitfield_store_after_debug_read_adapter<DT, ADAPTER>::
operator()(DT& value, const DT& bitMask)
{
  if (mAdapter(value, bitMask)) {
    mBitfield.put_debug(value, bitMask);
    return true;
  }

  return false;
}

}

#endif

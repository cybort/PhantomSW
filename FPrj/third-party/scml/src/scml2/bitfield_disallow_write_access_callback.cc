/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/bitfield_disallow_write_access_callback.h>

#include <scml2/utils.h>

namespace scml2 {

template <typename DT>
inline
bool
bitfield_disallow_write_access_callback<DT>::
write(const DT&, const DT&, sc_core::sc_time&)
{
  return !mReturnError;
}

template <typename DT>
inline
bool
bitfield_disallow_write_access_callback<DT>::
has_never_syncing_behavior() const
{
  return true;
}

#define SCML2_INSTANTIATE_TEMPLATE(type) \
  template class bitfield_disallow_write_access_callback<type>;
SCML2_FOR_EACH_DT(SCML2_INSTANTIATE_TEMPLATE)
#undef SCML2_INSTANTIATE_TEMPLATE

}

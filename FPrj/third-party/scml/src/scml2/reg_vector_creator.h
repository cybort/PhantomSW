/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_REG_VECTOR_CREATOR_H
#define SCML2_REG_VECTOR_CREATOR_H

#include <scml2/reg.h>

namespace scml2 {

template <typename DT>
class memory;

template <typename DT, typename T = scml2::reg<DT> >
class reg_vector_creator
{
public:
  reg_vector_creator(scml2::memory<DT>& parent, size_t offset = 0, size_t spacing = 0) : mParent(parent), mOffset(offset), mSpacing(spacing) {
  }

  T* operator()(const char* prefix, size_t i) {
    return new T(prefix, mParent, mOffset + i*(mSpacing+1));
  }

private:
  scml2::memory<DT>& mParent;
  size_t mOffset;
  size_t mSpacing;
};

template <typename DT>
inline reg_vector_creator<DT>
create_reg_vector_creator(scml2::memory<DT>& parent, size_t offset = 0, size_t spacing = 0) {
  return reg_vector_creator<DT>(parent, offset, spacing);
}

}

#endif

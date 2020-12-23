/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_WRITE_ADAPTER_H
#define SCML2_WRITE_ADAPTER_H

#include <scml2/streams.h>
#include <scml2_logging/stream.h>
#include <cassert>

namespace sc_core {
  class sc_time;
}

namespace scml2 {

template <typename M, typename C>
class write_adapter

{
public:
  typedef typename M::data_type data_type;
  typedef bool (C::*CallbackType)(const data_type& data,
                                  const data_type& byteEnables,
                                  sc_core::sc_time&);

public:
  write_adapter(C& c, CallbackType cb, const M& mem);

  bool operator()(const data_type& data,
                  const data_type& byteEnables,
                  sc_core::sc_time& t);

private:
  C& mClass;
  CallbackType mCallback;
};

template <typename M, typename C>
inline
write_adapter<M, C>
create_write_adapter(C& c,
                     typename write_adapter<M, C>::CallbackType cb,
                     const M& mem)
{
  return write_adapter<M, C>(c, cb, mem);
}

template <typename M, typename C>
inline
write_adapter<M, C>::
write_adapter(C& c, CallbackType cb, const M& mem) :
  mClass(c),
  mCallback(cb)
{
  if (mem.get_size() > 1) {
    SCML2_LOG(mem.get_streams().error())
      << "write_adapter only supported for memory objects of size 1, "
      << "memory '" << mem.get_name() << "' has size " << mem.get_size()
      << std::endl;
  }
}

template <typename M, typename C>
inline
bool
write_adapter<M, C>::
operator()(const data_type& data,
           const data_type& byteEnables,
           sc_core::sc_time& t)
{
  assert(mCallback);
  return (mClass.*mCallback)(data, byteEnables, t);
}

}

#endif

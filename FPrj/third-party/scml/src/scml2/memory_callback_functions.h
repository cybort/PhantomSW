/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_MEMORY_CALLBACK_FUNCTIONS_H
#define SCML2_MEMORY_CALLBACK_FUNCTIONS_H

#include <scml2/memory_callback.h>
#include <scml2/transport_adapter.h>
#include <scml2/read_adapter.h>
#include <scml2/null_adapter.h>
#include <scml2/on_write_adapter.h>
#include <scml2/write_adapter.h>
#include <scml2/transport_adapter_tagged.h>
#include <scml2/read_adapter_tagged.h>
#include <scml2/write_adapter_tagged.h>
#include <scml2/untimed_transport_adapter.h>
#include <scml2/untimed_read_adapter.h>
#include <scml2/untimed_write_adapter.h>
#include <scml2/untimed_transport_adapter_tagged.h>
#include <scml2/untimed_read_adapter_tagged.h>
#include <scml2/untimed_write_adapter_tagged.h>
#include <scml2/store_after_read_adapter.h>
#include <scml2/memory_disallow_access_callback.h>
#include <scml2/default_behavior_adapter.h>
#include <scml2/set_on_read_adapter.h>
#include <scml2/word_read_adapter.h>
#include <scml2/word_read_adapter_tagged.h>
#include <scml2/word_write_adapter.h>
#include <scml2/word_write_adapter_tagged.h>
#include <scml2/untimed_word_read_adapter.h>
#include <scml2/untimed_word_read_adapter_tagged.h>
#include <scml2/untimed_word_write_adapter.h>
#include <scml2/untimed_word_write_adapter_tagged.h>
#include <scml2/post_write_adapter.h>
#include <scml2/post_write_adapter_tagged.h>
#include <scml2/word_access_unroller.h>
#include <scml2/streams.h>
#include <scml2/types.h>

#include <scml2_logging/stream.h>
#include <string>
#include <cassert>

namespace scml2 {

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_callback(MEM_OBJECT<DT>& mem,
             C* c,
             typename transport_adapter<C>::CallbackType cb,
             const std::string& cbName,
             SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename transport_adapter<C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename transport_adapter<C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_transport_adapter(*c, cb),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_access_unroller<DT>(
          create_read_adapter(*c, cb, mem)),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_access_unroller<DT>(
        create_write_adapter(*c, cb, mem)),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_callback(MEM_OBJECT<DT>& mem,
             C* c,
             typename transport_adapter_tagged<C>::CallbackType cb,
             const std::string& cbName,
             SyncType syncType,
             int id)
{
  assert(c);
  mem.set_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb, id),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename transport_adapter_tagged<C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb, id),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename transport_adapter_tagged<C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_transport_adapter(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_access_unroller<DT>(
          create_read_adapter(*c, cb, id, mem)),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_access_unroller<DT>(
        create_write_adapter(*c, cb, id, mem)),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_callback(MEM_OBJECT<DT>& mem,
             C* c,
             typename untimed_transport_adapter<C>::CallbackType cb,
             const std::string& cbName,
             SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename untimed_transport_adapter<C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename untimed_transport_adapter<C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_transport_adapter(*c, cb),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename untimed_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_access_unroller<DT>(
          create_read_adapter(*c, cb, mem)),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename untimed_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_access_unroller<DT>(
        create_write_adapter(*c, cb, mem)),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_callback(MEM_OBJECT<DT>& mem,
             C* c,
             typename untimed_transport_adapter_tagged<C>::CallbackType cb,
             const std::string& cbName,
             SyncType syncType,
             int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb, id),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename untimed_transport_adapter_tagged<C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_transport_adapter(*c, cb, id),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename untimed_transport_adapter_tagged<C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_transport_adapter(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_read_callback(MEM_OBJECT<DT>& mem,
                  C* c,
                  typename untimed_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_access_unroller<DT>(
          create_read_adapter(*c, cb, id, mem)),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_write_callback(MEM_OBJECT<DT>& mem,
                   C* c,
                   typename untimed_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_access_unroller<DT>(
        create_write_adapter(*c, cb, id, mem)),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_read_callback(MEM_OBJECT<DT>& mem,
                       C* c,
                       typename word_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                       const std::string& cbName,
                       SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_read_adapter(*c, cb, mem),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename word_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_write_adapter(*c, cb, mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_read_callback(MEM_OBJECT<DT>& mem,
                       C* c,
                       typename word_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                       const std::string& cbName,
                       SyncType syncType,
                       int id)
{
  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_read_adapter(*c, cb, id, mem),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename word_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType,
                        int id)
{
  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_write_adapter(*c, cb, id, mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_read_callback(MEM_OBJECT<DT>& mem,
                       C* c,
                       typename untimed_word_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                       const std::string& cbName,
                       SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_read_adapter(*c, cb, mem),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename untimed_word_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_write_adapter(*c, cb, mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_read_callback(MEM_OBJECT<DT>& mem,
                       C* c,
                       typename untimed_word_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                       const std::string& cbName,
                       SyncType syncType,
                       int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_read_callback(
    create_memory_callback(
      create_store_after_read_adapter(
        create_word_read_adapter(*c, cb, id, mem),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_word_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType,
                        int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_word_write_adapter(*c, cb, id, mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_post_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename post_write_adapter<C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_default_behavior_adapter(
        create_post_write_adapter(*c, cb),
        mem),
      cbName,
      syncType));
}

template <typename DT, template <typename> class MEM_OBJECT, typename C>
inline
void
set_post_write_callback(MEM_OBJECT<DT>& mem,
                        C* c,
                        typename post_write_adapter_tagged<C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType,
                        int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(mem.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << mem.get_name() << "'"
      << std::endl;
  }

  assert(c);
  mem.set_write_callback(
    create_memory_callback(
      create_default_behavior_adapter(
        create_post_write_adapter(*c, cb, id),
        mem),
      cbName,
      syncType));
}

// *_on_read

#define SCML2_DEFINE_ON_READ_FUNCTION(function, set_value) \
  template <typename DT, template <typename> class MEM_OBJECT> \
  inline void set_##function(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING) \
  { \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_default_behavior_adapter(null_adapter(), mem), \
          mem, \
          set_value), \
        "<" #function ">", \
        syncType)); \
  } \
 \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    assert(c); \
    mem.set_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_transport_adapter(*c, cb), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
 \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_access_unroller<DT>( \
            create_read_adapter(*c, cb, mem)), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
 \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_transport_adapter(*c, cb, id), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
 \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_access_unroller<DT>( \
            create_read_adapter(*c, cb, id, mem)), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
   \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_transport_adapter(*c, cb), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
    \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_access_unroller<DT>( \
            create_read_adapter(*c, cb, mem)), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
    \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_transport_adapter(*c, cb, id), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
 \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_access_unroller<DT>( \
            create_read_adapter(*c, cb, id, mem)), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_read_adapter(*c, cb, mem), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename word_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_read_adapter(*c, cb, id, mem), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
    \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_read_adapter(*c, cb, mem), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_read_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
   \
    assert(c); \
    mem.set_read_callback( \
      create_memory_callback( \
        create_set_on_read_adapter( \
          create_word_read_adapter(*c, cb, id, mem), \
          mem, \
          set_value), \
        cbName, \
        syncType)); \
  }

SCML2_DEFINE_ON_READ_FUNCTION(clear_on_read, (DT) 0x0)
SCML2_DEFINE_ON_READ_FUNCTION(set_on_read, ~(DT) 0x0)

// -----------------------------------------------------------------------------
// *_on_write_*
// -----------------------------------------------------------------------------

#define SCML2_DEFINE_ON_WRITE_FUNCTION(function) \
  template <typename DT, template <typename> class MEM_OBJECT>  \
  inline void set_##function(MEM_OBJECT<DT>& mem, SyncType syncType = AUTO_SYNCING)  \
  {  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<false>(  \
          null_adapter(),  \
          mem),  \
        "<" #function ">",  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)  \
  {  \
    assert(c);  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<false>(  \
          create_transport_adapter(*c, cb),  \
          mem),  \
        cbName,  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline  \
  void  \
  set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)  \
  {  \
    assert(c);  \
    mem.set_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<false>(  \
          create_word_access_unroller<DT>(  \
            create_write_adapter(*c, cb, mem)),  \
          mem),  \
        cbName,  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)  \
  {  \
    assert(c);  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<false>(  \
          create_transport_adapter(*c, cb, id),  \
          mem),  \
        cbName,  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)  \
  {  \
    assert(c);  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<false>(  \
          create_word_access_unroller<DT>(  \
            create_write_adapter(*c, cb, id, mem)),  \
          mem),  \
        cbName,  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
   \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_transport_adapter(*c, cb), \
          mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
 \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_access_unroller<DT>( \
            create_write_adapter(*c, cb, mem)), \
          mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_transport_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
   \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_transport_adapter(*c, cb, id), \
          mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
    \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_access_unroller<DT>( \
            create_write_adapter(*c, cb, id, mem)), \
          mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_write_adapter(*c, cb, mem), \
        mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename word_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_write_adapter(*c, cb, id, mem), \
        mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
  \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_write_adapter(*c, cb, mem), \
        mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C> \
  inline void set_word_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename untimed_word_write_adapter_tagged<MEM_OBJECT<DT>, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) \
  { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(mem.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << mem.get_name() << "'" \
        << std::endl; \
    } \
   \
    assert(c); \
    mem.set_write_callback( \
      create_memory_callback( \
        create_##function##_adapter<false>( \
          create_word_write_adapter(*c, cb, id, mem), \
        mem), \
        cbName, \
        syncType)); \
  } \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline void set_post_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter<C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)  \
  {  \
    if (syncType == SELF_SYNCING) {  \
      SCML2_LOG(mem.get_streams().error())  \
        << "SELF_SYNCING not supported for untimed callbacks on '"  \
        << mem.get_name() << "'"  \
        << std::endl;  \
    }  \
  \
    assert(c);  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<true>(  \
          create_post_write_adapter(*c, cb),  \
          mem), \
        cbName,  \
        syncType));  \
  }  \
  \
  template <typename DT, template <typename> class MEM_OBJECT, typename C>  \
  inline void set_post_##function##_callback(MEM_OBJECT<DT>& mem, C* c, typename post_write_adapter_tagged<C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)  \
  {  \
    if (syncType == SELF_SYNCING) {  \
      SCML2_LOG(mem.get_streams().error())  \
        << "SELF_SYNCING not supported for untimed callbacks on '"  \
        << mem.get_name() << "'"  \
        << std::endl;  \
    }  \
  \
    assert(c);  \
    mem.set_write_callback(  \
      create_memory_callback(  \
        create_##function##_adapter<true>(  \
          create_post_write_adapter(*c, cb, id),  \
          mem), \
        cbName,  \
        syncType));  \
  } 

SCML2_DEFINE_ON_WRITE_FUNCTION(clear_on_write_0)
SCML2_DEFINE_ON_WRITE_FUNCTION(clear_on_write_1)
SCML2_DEFINE_ON_WRITE_FUNCTION(set_on_write_0)
SCML2_DEFINE_ON_WRITE_FUNCTION(set_on_write_1)

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_access(MEM_OBJECT<DT>& mem)
{
  mem.set_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_read_access(MEM_OBJECT<DT>& mem)
{
  mem.set_read_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_ignore_write_access(MEM_OBJECT<DT>& mem)
{
  mem.set_write_callback(new scml2::memory_disallow_access_callback(false));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_access(MEM_OBJECT<DT>& mem)
{
  mem.set_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_read_access(MEM_OBJECT<DT>& mem)
{
  mem.set_read_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_disallow_write_access(MEM_OBJECT<DT>& mem)
{
  mem.set_write_callback(new scml2::memory_disallow_access_callback(true));
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_read_only(MEM_OBJECT<DT>& mem)
{
  set_disallow_write_access(mem);
}

template <typename DT, template <typename> class MEM_OBJECT>
inline
void
set_write_only(MEM_OBJECT<DT>& mem)
{
  set_disallow_read_access(mem);
}

}

#endif

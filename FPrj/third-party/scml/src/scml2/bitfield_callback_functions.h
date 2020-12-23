/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#ifndef SCML2_BITFIELD_CALLBACK_FUNCTIONS_H
#define SCML2_BITFIELD_CALLBACK_FUNCTIONS_H

#include <scml2/bitfield_read_callback.h>
#include <scml2/bitfield_write_callback.h>
#include <scml2/bitfield_read_adapter.h>
#include <scml2/bitfield_write_adapter.h>
#include <scml2/bitfield_read_adapter_tagged.h>
#include <scml2/bitfield_write_adapter_tagged.h>
#include <scml2/bitfield_untimed_read_adapter.h>
#include <scml2/bitfield_untimed_write_adapter.h>
#include <scml2/bitfield_untimed_read_adapter_tagged.h>
#include <scml2/bitfield_untimed_write_adapter_tagged.h>
#include <scml2/bitfield_mask_read_adapter.h>
#include <scml2/bitfield_mask_write_adapter.h>
#include <scml2/bitfield_mask_read_adapter_tagged.h>
#include <scml2/bitfield_mask_write_adapter_tagged.h>
#include <scml2/bitfield_untimed_mask_read_adapter.h>
#include <scml2/bitfield_untimed_mask_write_adapter.h>
#include <scml2/bitfield_untimed_mask_read_adapter_tagged.h>
#include <scml2/bitfield_untimed_mask_write_adapter_tagged.h>
#include <scml2/bitfield_disallow_read_access_callback.h>
#include <scml2/bitfield_disallow_write_access_callback.h>
#include <scml2/bitfield_on_write_adapter.h>
#include <scml2/bitfield_post_write_adapter.h>
#include <scml2/bitfield_post_write_adapter_tagged.h>
#include <scml2/bitfield_store_after_read_adapter.h>
#include <scml2/bitfield_default_read_behavior_adapter.h>
#include <scml2/bitfield_default_write_behavior_adapter.h>
#include <scml2/bitfield_null_adapter.h>
#include <scml2/bitfield_set_on_read_adapter.h>
#include <scml2/bitfield.h>
#include <scml2/streams.h>
#include <scml2/types.h>

#include <scml2_logging/stream.h>
#include <string>
#include <cassert>

namespace scml2 {

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_read_adapter<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_write_adapter<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_read_adapter_tagged<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_write_adapter_tagged<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_untimed_read_adapter<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_untimed_write_adapter<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_untimed_read_adapter_tagged<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_untimed_write_adapter_tagged<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_mask_read_adapter<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_mask_write_adapter<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_mask_read_adapter_tagged<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_mask_write_adapter_tagged<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_untimed_mask_read_adapter<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_untimed_mask_write_adapter<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_read_callback(bitfield<DT>& bitfield,
                  C* c,
                  typename bitfield_untimed_mask_read_adapter_tagged<DT, C>::CallbackType cb,
                  const std::string& cbName,
                  SyncType syncType,
                  int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_store_after_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_write_callback(bitfield<DT>& bitfield,
                   C* c,
                   typename bitfield_untimed_mask_write_adapter_tagged<DT, C>::CallbackType cb,
                   const std::string& cbName,
                   SyncType syncType,
                   int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_write_adapter<DT>(*c, cb, id),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_post_write_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_post_write_adapter<DT, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_default_write_behavior_adapter(
        create_bitfield_post_write_adapter<DT>(*c, cb),
        bitfield),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline
void
set_post_write_callback(bitfield<DT>& bitfield,
                        C* c,
                        typename bitfield_post_write_adapter_tagged<DT, C>::CallbackType cb,
                        const std::string& cbName,
                        SyncType syncType,
                        int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_write_callback(
    create_bitfield_write_callback<DT>(
      create_bitfield_default_write_behavior_adapter(
        create_bitfield_post_write_adapter<DT>(*c, cb, id),
        bitfield),
      cbName,
      syncType));
}

template <typename DT>
inline
void
set_ignore_read_access(bitfield<DT>& bitfield)
{
  bitfield.set_read_callback(new scml2::bitfield_disallow_read_access_callback<DT>(false));
}

template <typename DT>
inline
void
set_ignore_write_access(bitfield<DT>& bitfield)
{
  bitfield.set_write_callback(new scml2::bitfield_disallow_write_access_callback<DT>(false));
}

template <typename DT>
inline
void
set_ignore_access(bitfield<DT>& bitfield)
{
  set_ignore_read_access(bitfield);
  set_ignore_write_access(bitfield);
}

template <typename DT>
inline
void
set_disallow_read_access(bitfield<DT>& bitfield)
{
  bitfield.set_read_callback(new scml2::bitfield_disallow_read_access_callback<DT>(true));
}

template <typename DT>
inline
void
set_disallow_write_access(bitfield<DT>& bitfield)
{
  bitfield.set_write_callback(new scml2::bitfield_disallow_write_access_callback<DT>(true));
}

template <typename DT>
inline
void
set_disallow_access(bitfield<DT>& bitfield)
{
  set_disallow_read_access(bitfield);
  set_disallow_write_access(bitfield);
}

template <typename DT>
inline
void
set_read_only(bitfield<DT>& bitfield)
{
  set_disallow_write_access(bitfield);
}

template <typename DT>
inline
void
set_write_only(bitfield<DT>& bitfield)
{
  set_disallow_read_access(bitfield);
}

// -----------------------------------------------------------------------------
// clear_on_read
// -----------------------------------------------------------------------------

template <typename DT>
inline void set_clear_on_read(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING)
{
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_default_read_behavior_adapter<DT>(bitfield_null_adapter<DT>(), bitfield),
        bitfield,
        0x0),
      "<clear on read>",
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        0x0),
      cbName,
      syncType));
}
template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_clear_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        0x0),
      cbName,
      syncType));
}


// -----------------------------------------------------------------------------
// set_on_read
// -----------------------------------------------------------------------------

template <typename DT>
inline void set_set_on_read(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING)
{
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_default_read_behavior_adapter<DT>(bitfield_null_adapter<DT>(), bitfield),
        bitfield,
        ~(DT)0x0),
      "<clear on read>",
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}
template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

template <typename DT, typename C>
inline void set_set_on_read_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_read_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id)
{
  if (syncType == SELF_SYNCING) {
    SCML2_LOG(bitfield.get_streams().error())
      << "SELF_SYNCING not supported for untimed callbacks on '"
      << bitfield.get_name() << "'"
      << std::endl;
  }

  assert(c);
  bitfield.set_read_callback(
    create_bitfield_read_callback<DT>(
      create_bitfield_set_on_read_adapter<DT>(
        create_bitfield_read_adapter<DT>(*c, cb, id),
        bitfield,
        ~(DT)0x0),
      cbName,
      syncType));
}

// -----------------------------------------------------------------------------
// *_on_write_*
// -----------------------------------------------------------------------------

#define SCML2_DEFINE_BITFIELD_ON_WRITE_FUNCTION(function) \
  template <typename DT> \
  inline void set_##function(bitfield<DT>& bitfield, SyncType syncType = AUTO_SYNCING) \
  { \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          bitfield_null_adapter<DT>(), \
          bitfield), \
        "<" #function ">", \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) { \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_write_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) { \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb, id), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C>  \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_write_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb, id), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) { \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_mask_write_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) { \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb, id), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_untimed_mask_write_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<false>( \
          create_bitfield_write_adapter<DT>(*c, cb, id), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_post_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType = AUTO_SYNCING) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<true>( \
          create_bitfield_post_write_adapter<DT>(*c, cb), \
          bitfield), \
        cbName, \
        syncType)); \
  } \
   \
  template <typename DT, typename C> \
  inline void set_post_##function##_callback(bitfield<DT>& bitfield, C* c, typename bitfield_post_write_adapter_tagged<DT, C>::CallbackType cb, const std::string& cbName, SyncType syncType, int id) { \
    if (syncType == SELF_SYNCING) { \
      SCML2_LOG(bitfield.get_streams().error()) \
        << "SELF_SYNCING not supported for untimed callbacks on '" \
        << bitfield.get_name() << "'" \
        << std::endl; \
    } \
    assert(c); \
    bitfield.set_write_callback( \
      create_bitfield_write_callback<DT>( \
        create_bitfield_##function##_adapter<true>( \
          create_bitfield_post_write_adapter<DT>(*c, cb, id), \
          bitfield), \
        cbName, \
        syncType)); \
  }

SCML2_DEFINE_BITFIELD_ON_WRITE_FUNCTION(clear_on_write_0)
SCML2_DEFINE_BITFIELD_ON_WRITE_FUNCTION(clear_on_write_1)
SCML2_DEFINE_BITFIELD_ON_WRITE_FUNCTION(set_on_write_0)
SCML2_DEFINE_BITFIELD_ON_WRITE_FUNCTION(set_on_write_1)

}

#endif

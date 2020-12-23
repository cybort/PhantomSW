/******************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  **
 *       This software and the associated documentation are confidential     **
 *                  and proprietary to Synopsys, Inc.                        **
 *        Your use or disclosure of this software is subject                 **
 *      to the terms and conditions of a written license agreement           **
 *           between you, or your company, and Synopsys, Inc.                **
 *                                                                           **
 *****************************************************************************/
#ifndef SCML2_STREAMS_H
#define SCML2_STREAMS_H

#include <scml2_logging/stream.h>
#include <scml2_logging/severity.h>
#include <string>

namespace scml2 {

class streams
{
public:
  explicit streams(const std::string& name);
  virtual ~streams();

  logging::stream& internal_error() const;
  logging::stream& error() const;

private:
  mutable logging::stream mInternalError;
  mutable logging::stream mError;
};

inline
streams::
streams(const std::string& name) :
  mInternalError(name, logging::severity::internal_error()),
  mError(name, logging::severity::error())
{
}

inline
streams::
~streams()
{
}

inline
logging::stream&
streams::
internal_error() const
{
  return mInternalError;
}

inline
logging::stream&
streams::
error() const
{
  return mError;
}

}

#endif

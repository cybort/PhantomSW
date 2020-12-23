/*****************************************************************************
 *                   Copyright (C) 2009-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
#include <scml2/memory_heap_storage.h>
#include <scml2/toplevel_memory_base.h>
#include <scml2/streams.h>

#include <scml2_logging/stream.h>
#include <limits>
#include <sys/mman.h>
#include <fcntl.h>
#include <map>
std::string m_scml_log_path = "./";

typedef std::map<std::string, unsigned char*> MemoryMappedInfo;
MemoryMappedInfo mMemoryMappedInfo;

unsigned char* get_map_ptr(std::string filename)
{
	if( mMemoryMappedInfo.count(filename) > 0 )
		return mMemoryMappedInfo[filename];
	return NULL;
}

namespace scml2 {

#define MIN_SIZE_FOR_MAP_CREATE		0x4000

static void *create_map( std::string objname , const unsigned long long size, int *file_descriptor )
{
	std::string sFileName = m_scml_log_path + "/" + objname + ".dat";
	int iFileDescriptor = open(sFileName.c_str() , O_RDWR|O_TRUNC|O_CREAT, S_IRWXU+S_IRGRP+S_IRWXO);
	*file_descriptor = iFileDescriptor;
	lseek( iFileDescriptor, size - 1, SEEK_SET);
	write( iFileDescriptor,"", 1);
	return mmap(NULL , size  , PROT_READ | PROT_WRITE, MAP_SHARED, iFileDescriptor, 0);
}

memory_heap_storage::
memory_heap_storage(toplevel_memory_base& m, const std::string& filename) :
  mMemory(m)
{
  if (m.get_size()) {
    const unsigned long long size =
      index_to_address(m.get_size(), m.get_width());
    if (size > std::numeric_limits<std::size_t>::max()) {
      SCML2_LOG(m.get_streams().error())
        << "The size (0x" << std::hex << size << ") of memory '"
        << m.get_name() << "' is to big to be allocated on the heap."
        << std::dec << std::endl;
    }
    if( (size >= MIN_SIZE_FOR_MAP_CREATE) && (!filename.empty() ))
    {
    	mStorage = (unsigned char*)create_map( filename , size, &file_descriptor);
    	mMemoryMappedInfo[filename] = mStorage;
    	m_b_is_storage_map = true;
    	m_ull_storage_size = size;
    }
    else
    {
    	mStorage = new unsigned char[size];
    	m_b_is_storage_map = false;
    }

  } else {
    mStorage = 0;
  }
}

memory_heap_storage::
memory_heap_storage(toplevel_memory_base& m) :
  mMemory(m)
{
  if (m.get_size()) {
    const unsigned long long size =
      index_to_address(m.get_size(), m.get_width());
    if (size > std::numeric_limits<std::size_t>::max()) {
      SCML2_LOG(m.get_streams().error())
        << "The size (0x" << std::hex << size << ") of memory '"
        << m.get_name() << "' is to big to be allocated on the heap."
        << std::dec << std::endl;
    }

	mStorage = new unsigned char[size];
	m_b_is_storage_map = false;

  } else {
    mStorage = 0;
  }
}

memory_heap_storage::
~memory_heap_storage()
{
	if( m_b_is_storage_map)
	{
		munmap(mStorage ,m_ull_storage_size);
		close(file_descriptor);
	}
	else
	{
		delete [] mStorage;
	}
}

unsigned char*
memory_heap_storage::
get_fast_backdoor() const
{
  return mStorage;
}

memory_storage_base::fast_backdoor_region
memory_heap_storage::
get_fast_backdoor(unsigned long long)
{
  fast_backdoor_region region;
  region.startAddress = 0x0;
  region.endAddress = index_to_address(mMemory.get_size(),
                                       mMemory.get_width());
  region.fastBackdoor = mStorage;
  return region;
}

void
memory_heap_storage::
read(unsigned long long address,
     unsigned char* data,
     unsigned int size) const
{
  memcpy(data, mStorage + address, size);
}

void
memory_heap_storage::
write(unsigned long long address,
      const unsigned char* data,
      unsigned int size)
{
  memcpy(mStorage + address, data, size);
}

memory_storage_base*
memory_heap_storage::
create_storage(toplevel_memory_base& m)
{
  return new memory_heap_storage(m);
}

memory_storage_base*
memory_heap_storage::
create_storage(toplevel_memory_base& m, const std::string& filename)
{
  return new memory_heap_storage(m,filename);
}

}

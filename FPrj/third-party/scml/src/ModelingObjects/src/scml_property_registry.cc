/*****************************************************************************
 *                   Copyright (C) 1996-2010 Synopsys, Inc.                  *
 *       This software and the associated documentation are confidential     *
 *                  and proprietary to Synopsys, Inc.                        *
 *        Your use or disclosure of this software is subject                 *
 *      to the terms and conditions of a written license agreement           *
 *           between you, or your company, and Synopsys, Inc.                *
 *                                                                           *
 *****************************************************************************/
/*
 * Modifications :
 *
 * Purpose of file : Implementation file for scml_property_registry
 *
 */

#include "scml_property_registry.h"
#include "scml_property_server_if.h"

#include <sys/stat.h>
#include <cassert>


using std::string;
using std::cerr;
using std::endl;

static const char* const TAG_PARAMETERS    	      = "parameters";
static const char* const TAG_PARAMETER    	      = "parameter";
static const char* const TAG_CONSTRUCTOR_ARGUMENTS    = "constructor_arguments";
static const char* const TAG_PROTOCOL_PARAMETERS      = "protocol_parameters";
static const char* const TAG_MODULES                  = "modules";
static const char* const TAG_MODULE                   = "module";
static const char* const TAG_PORTS                    = "ports";
static const char* const TAG_PORT                     = "port";
static const char* const TAG_NAME                     = "name";
static const char* const TAG_VALUE                    = "value";

static const char* const TAG_PORT_ARRAYS              = "port_arrays";
static const char* const TAG_PORT_ARRAY               = "port_array";

scml_property_registry& scml_property_registry::inst() 
{
  static scml_property_registry instance;
  return instance;
}

scml_property_registry::scml_property_registry() : 
  mOs( &cerr), 
  mCustomPropServer( 0)
{
}

scml_property_registry::~scml_property_registry()
{
}

bool scml_property_registry::setCustomPropertyServer( scml_property_server_if * p )
{
  mCustomPropServer = p;
  return (0 != mCustomPropServer);
}


long long scml_property_registry::getIntProperty(PropertyType type, 
				        	 const string& moduleName, 
  		   		        	 const string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( moduleName + '.' + name);
    return mCustomPropServer->getIntProperty( completeName);
  } else {
  }
  return 0;
}
		   
unsigned long long scml_property_registry::getUIntProperty(PropertyType type, 
				        	    const string& moduleName, 
  		   		        	    const string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( moduleName + '.' + name);
    return mCustomPropServer->getUIntProperty( completeName);
  } else {
  }
  return 0;
}

bool scml_property_registry::getBoolProperty(PropertyType type, 
					     const string& moduleName, 
   		     			     const string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( moduleName + '.' + name);

    return mCustomPropServer->getBoolProperty( completeName);
  } else {
  }
  return false;
}
				       
string scml_property_registry::getStringProperty(PropertyType type, 
						 const string& moduleName, 
  			        		 const string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( moduleName + '.' + name);
    return mCustomPropServer->getStringProperty( completeName);
  } else {
  }
  return "";
}
					   
double scml_property_registry::getDoubleProperty(PropertyType type, 
						 const string& moduleName, 
  			 			 const string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( moduleName + '.' + name);
    return mCustomPropServer->getDoubleProperty( completeName);
  } else {
  }
  return 0.0;
}

bool scml_property_registry::hasProperty(PropertyType type, 
					 PropertyCType ctype, 
    		 			 const std::string& scHierName, 
					 const std::string& name)
{
  if( 0 != mCustomPropServer) {
    const string completeName( scHierName + '.' + name);
    switch (ctype) {
      case SIGNED_INTEGER:
        return mCustomPropServer->hasIntProperty(completeName);
      case UNSIGNED_INTEGER:
        return mCustomPropServer->hasUIntProperty(completeName);
      case INTEGER:
        return mCustomPropServer->hasIntProperty(completeName) ||
               mCustomPropServer->hasUIntProperty(completeName);
      case STRING:
        return mCustomPropServer->hasStringProperty(completeName);
      case BOOL:
        return mCustomPropServer->hasBoolProperty(completeName);
      case DOUBLE:
        return mCustomPropServer->hasDoubleProperty(completeName);
      default:
        assert(0);
    }
  }
  return false;
}

// transform myMod.subMod/a to myMod/subMod.a
static bool shiftDot (string& module_name, string& param_name) 
{
   if (module_name.find(".") != string::npos) {
     string afterDot(module_name, module_name.rfind(".") + 1, string::npos);
     param_name = afterDot + "." + param_name;
     module_name.erase(module_name.rfind("."), string::npos);
     return true;
   }
   return false;
}


void scml_property_registry::setOutputStream(::std::ostream* output)
{
  mOs = output;
}

std::string scml_property_registry::getPropertyXmlFilePath() const
{
  return mXmlFilePath;
}  

static bool exists(const std::string& filename)
{
  struct stat st; 
  return (stat(filename.c_str(), &st) == 0) ? true : false;
}

void scml_property_registry::setXMLFile(const string& fileName)
{
}


############################################################################
#
#
#  Project:          
#  Description:     common project makefile
#  Notes:
#
#############################################################################

#---------------------------------------------------------------------------
#
# Project definitions
#
#---------------------------------------------------------------------------

# Project name
PROJ_NAME =ppyy

# Default target when none is given on the command line
$(PROJ_NAME):

# Project folder
# This line must be before all include to other Makefiles
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# Check on must set variables

# Include local makefile
include $(BASE_DIR)/build.mk

# Project folders
SRC_DIR = $(BASE_DIR)/$(COMMON_SRC_DIR_NAME)
OBJ_DIR = $(BASE_DIR)/$(COMMON_BUILD_DIR_NAME)/$(COMMON_OBJ_DIR_NAME)
BIN_DIR = $(BASE_DIR)/$(COMMON_BIN_DIR_NAME)
INCLUDE_DIR = $(BASE_DIR)/$(COMMON_INCLUDE_DIR_NAME)
# Project source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Project target objects
OBJS := $(patsubst $(BASE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
BIN_FILE = $(PROJ_NAME)_$(COMMON_PLATFORM)
BIN = $(BIN_DIR)/$(BIN_FILE)
LIBS += ./systemC/lib/lib-linux64/libsystemc.a


#---------------------------------------------------------------------------
#
# Project flags
#
#---------------------------------------------------------------------------

# Project cflags
CFLAGS += $(COMMON_CPE_WARNINGS)
#CFLAGS += $(COMMON_EZCHIP_CFLAGS)
#CFLAGS += $(COMMON_CPE_CFLAGS)
CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -I./systemC/lib/include
CFLAGS += -I./tlm/include
CFLAGS += -pthread
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-parameter

# Project ldflags
LDFLAGS += -pthread
LDFLAGS += -lm
LDFLAGS += -lrt


DEFS = -DSC_USE_STD_STRING
# Debug/Release flags
ifdef COMMON_NDEBUG
COMMON_FLAGS = $(COMMON_RELEASE_OPT_LEVEL)
CFLAGS += $(COMMON_RELEASE_FLAGS)
CFLAGS += $(COMMON_RELEASE_LOG_LEVEL)
else
COMMON_FLAGS = $(COMMON_DEBUG_OPT_LEVEL)
CFLAGS += $(COMMON_DEBUG_FLAGS)
CFLAGS += $(COMMON_DEBUG_LOG_LEVEL)
endif

CFLAGS += $(COMMON_FLAGS)
LDFLAGS += $(COMMON_FLAGS)
#-DREADLINE_LIBRARY
EXTRA_CFLAGS += $(DEFS) 
# Extra cflags
ifneq ($(EXTRA_CFLAGS),)
CFLAGS += $(EXTRA_CFLAGS)
endif

# Extra ldflags
ifneq ($(EXTRA_LDFLAGS),)
LDFLAGS += $(EXTRA_LDFLAGS)
endif


#---------------------------------------------------------------------------
#
# Project targets
#
#---------------------------------------------------------------------------

# Project PHONY targets
.PHONY: $(call common_register_phony_targets,$(PROJ_NAME) clean)

# Human-friendly target
$(PROJ_NAME): $(BIN)

# ELF target
$(BIN): $(OBJS) $(LIBS) $(COMMON_FORCE)
	$(call common_cxx_ld_rule,$(OBJS) $(LIBS),$(LDFLAGS))

# Version object target
$(OBJ_DIR)/src/main.o: $(BASE_DIR)/src/main.cpp $(COMMON_FORCE)
	$(call common_cxx_o_rule,$(CFLAGS) $(COMMON_SCM_CFLAG))

# Object targets
$(OBJ_DIR)/%.o: $(BASE_DIR)/%.cpp $(COMMON_FORCE)
	$(call common_cxx_o_rule,$(CFLAGS))

# Dependency targets
$(LIBS):

# Clean target
clean:
	$(call common_clean_rule,$(OBJS) $(BIN))


# Include .d and .cmd files
include $(call common_include_dep_files,$(OBJS))
include $(call common_include_cmd_files,$(OBJS) $(BIN))


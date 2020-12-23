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
PROJ_NAME =app

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
SRCS := $(call common_rwildcard,$(SRC_DIR),*.c)
#SRCS += $(call common_rwildcard,$(SRC_DIR),*.c)
#SRCS += $(call common_rwildcard,$(SRC_DIR)/if,*.c)
#SRCS += $(call common_rwildcard,$(SRC_DIR)/tm,*.c)

# Project target objects
OBJS := $(patsubst $(BASE_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
BIN_FILE = $(PROJ_NAME)_$(COMMON_PLATFORM)
BIN = $(BIN_DIR)/$(BIN_FILE)
LIBS += ./lib/libhistory.a -ltermcap
LIBS += ./lib/libreadline.a


#---------------------------------------------------------------------------
#
# Project flags
#
#---------------------------------------------------------------------------

# Project cflags
CFLAGS += $(COMMON_CM_WARNINGS)

#CFLAGS += $(COMMON_CPE_CFLAGS)

#header files search path
CFLAGS += -I$(INCLUDE_DIR)
CFLAGS += -I$(SRC_DIR)
#CFLAGS += $(foreach dir,$(shell find $(SRC_DIR)/cli -type d),-I$(dir))
#CFLAGS += $(foreach dir,$(shell find $(SRC_DIR)/if -type d),-I$(dir))
#CFLAGS += $(foreach dir,$(shell find $(SRC_DIR)/tm -type d),-I$(dir))


#Compile flags
CFLAGS += -pthread
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-nested-externs
CFLAGS += -Wno-missing-prototypes
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-uninitialized
CFLAGS += -Wno-missing-declarations
CFLAGS += -Wno-implicit-function-declaration

# Project ldflags
LDFLAGS += -pthread
LDFLAGS += -lm
LDFLAGS += -lrt


DEFS = -DHAVE_CONFIG_H

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
	$(call common_cc_ld_rule,$(OBJS) $(LIBS),$(LDFLAGS))

# Version object target
$(OBJ_DIR)/src/main.o: $(BASE_DIR)/src/main.c $(COMMON_FORCE)
	$(call common_cc_o_rule,$(CFLAGS) $(COMMON_SCM_CFLAG))

# Object targets
$(OBJ_DIR)/%.o: $(BASE_DIR)/%.c $(COMMON_FORCE)
	$(call common_cc_o_rule,$(CFLAGS))

# Dependency targets
$(LIBS):

# Clean target
clean:
	$(call common_clean_rule,$(OBJS) $(BIN))


# Include .d and .cmd files
include $(call common_include_dep_files,$(OBJS))
include $(call common_include_cmd_files,$(OBJS) $(BIN))


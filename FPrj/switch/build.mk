############################################################################
#
#
# Redistribution and use in source and binary forms with or without
# modification are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the names of the copyright holders nor the names of its
#     contributors may be used to endorse or promote products derived from
#     this software without specific prior written permission.
#
#  Alternatively this software may be distributed under the terms of the
#  GNU General Public License (GPL) version 2 as published by the Free
#  Software Foundation.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
#  AND ANY EXPRESS OR IMPLIED WARRANTIES INCLUDING BUT NOT LIMITED TO THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT INDIRECT INCIDENTAL SPECIAL EXEMPLARY OR
#  CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO PROCUREMENT OF
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE DATA OR PROFITS; OR BUSINESS
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY WHETHER IN
#  CONTRACT STRICT LIABILITY OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#
#
#   Project:         demo_cp
#
#  Description:      demo_cp application build makefile
#  Notes:		To build for debug use D=1 from command line
#			To show build commands use V=1 from command line
#
#############################################################################

#---------------------------------------------------------------------------
#
# Default make definitions
#
#---------------------------------------------------------------------------

# Dont use make's built-in rules
MAKEFLAGS += -r --no-print-directory

# Define default shell
SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
		else if [ -x /bin/bash ]; then echo /bin/bash; \
		else echo sh; fi; fi)

# Dont pass command line variables to sub-makes
MAKEOVERRIDES =

# No need of updating the makefiles
Makefile: ;
%.mk :: ;
%.cmd :: ;
%.d :: ;


#---------------------------------------------------------------------------
#
# PHONY targets
#
#---------------------------------------------------------------------------

COMMON_FORCE = FORCE
COMMON_PHONY = $(COMMON_FORCE)
.PHONY: $(COMMON_FORCE)
$(COMMON_FORCE):

common_register_phony_targets =  $(1) $(eval COMMON_PHONY += $(1))


#---------------------------------------------------------------------------
#
# Common names
#
#---------------------------------------------------------------------------

ifneq ($(EZDK_TARGET_BOARD),)
   COMMON_TARGET_BOARD = $(EZDK_TARGET_BOARD)
else
   COMMON_TARGET_BOARD = sim
endif
COMMON_PLATFORM = linux_x86_64
COMMON_OBJ_DIR_NAME = Obj_$(COMMON_PLATFORM)
COMMON_SRC_DIR_NAME = src
COMMON_BUILD_DIR_NAME = build
COMMON_LIB_DIR_NAME = lib
COMMON_BIN_DIR_NAME = bin
COMMON_INCLUDE_DIR_NAME = include
COMMON_COMMA = ,
COMMON_EMPTY :=
COMMON_SPACE := $(COMMON_EMPTY) $(COMMON_EMPTY)


#---------------------------------------------------------------------------
#
# Verbose mode
# make V=0|1
#    0 => quiet build (default)
#    1 => verbose build
#
#---------------------------------------------------------------------------

ifeq ("$(origin V)", "command line")
# To really make V go away in submakes, we have to override it.
override V:=$(V)

EZDK_VERBOSE = $(V)
endif

ifndef EZDK_VERBOSE
EZDK_VERBOSE = 0
endif

ifeq ($(EZDK_VERBOSE),1)
quiet =
Q =
else
quiet = quiet_
Q = @
endif

ifneq ($(filter s% -s%,$(MAKEFLAGS)),)
quiet = silent_
endif

squote := '
escsq = $(subst $(squote),'\$(squote)',$1)

echo-cmd = $(if $($(quiet)cmd_$(1)),\
	echo '  $(call escsq,$($(quiet)cmd_$(1)))';)


#---------------------------------------------------------------------------
#
# Debug mode
# make D=0|1
#    0 => release build (default)
#    1 => debug build
#
#---------------------------------------------------------------------------

ifeq ("$(origin D)", "command line")
# To really make D go away in submakes, we have to override it.
override D:=$(D)
EZDK_DEBUG_LEVEL = $(D)
endif

ifndef EZDK_DEBUG_LEVEL
EZDK_DEBUG_LEVEL = 0
endif

ifeq ($(EZDK_DEBUG_LEVEL),0)
override COMMON_NDEBUG = TRUE
else
override COMMON_NDEBUG=
endif


#---------------------------------------------------------------------------
#
# x86_64 configure flags
#
#---------------------------------------------------------------------------

COMMON_CONFIGURE_FLAGS :=


#---------------------------------------------------------------------------
#
# x86_64 gcc flags
#
#---------------------------------------------------------------------------

# Create gcc dependency files with system headers
COMMON_GCC_GEN_SYS_HEADERS_DEPS = TRUE


#---------------------------------------------------------------------------
#
# Host Toolchain
#
#---------------------------------------------------------------------------

CROSS_COMPILE :=


#---------------------------------------------------------------------------
#
# Toolchain
#
#---------------------------------------------------------------------------

CC      := $(CROSS_COMPILE)gcc
CXX     := $(CROSS_COMPILE)g++
AR      := $(CROSS_COMPILE)ar
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
STRIP   := $(CROSS_COMPILE)strip

# Change toolchain to full path
CC      := $(shell PATH=$(PATH); which $(CC) 2>/dev/null || type -p $(CC) || echo $(CC))
CXX     := $(shell PATH=$(PATH); which $(CXX) 2>/dev/null || type -p $(CXX) || echo $(CXX))
AR      := $(shell PATH=$(PATH); which $(AR) 2>/dev/null || type -p $(AR) || echo $(AR))
OBJCOPY := $(shell PATH=$(PATH); which $(OBJCOPY) 2>/dev/null || type -p $(OBJCOPY) || echo $(OBJCOPY))
OBJDUMP := $(shell PATH=$(PATH); which $(OBJDUMP) 2>/dev/null || type -p $(OBJDUMP) || echo $(OBJDUMP))
STRIP   := $(shell PATH=$(PATH); which $(STRIP) 2>/dev/null || type -p $(STRIP) || echo $(STRIP))

LD      := $(CC)
CXXLD   := $(CXX)

# for some sources such as asm there is no added value of using
# ccache becuase it doesnt support the source language
CC_NO_PREFIX := $(CC)

# Add prefix to the compiler
# This can be used to run tools like ccache or distcc
ifdef EZDK_PREFIX
CC := $(EZDK_PREFIX) $(CC)
CXX := $(EZDK_PREFIX) $(CXX)
endif


#---------------------------------------------------------------------------
#
# Common c/c++ flags
#
#---------------------------------------------------------------------------

COMMON_CFLAGS += -pipe
ifneq ($(COMMON_GCC_GEN_SYS_HEADERS_DEPS),)
COMMON_CFLAGS += -MD
else
COMMON_CFLAGS += -MMD
endif
COMMON_CFLAGS += -MP
COMMON_CFLAGS += -MF"$(call common_dep_file_name,$@)"
COMMON_CFLAGS += -MT"$@"


#---------------------------------------------------------------------------
#
# Release/debug flags
#
#---------------------------------------------------------------------------

# Debug flags
COMMON_DEBUG_OPT_LEVEL = -O0
COMMON_DEBUG_FLAGS += -g

# Release flags
COMMON_RELEASE_OPT_LEVEL = -O2
COMMON_RELEASE_FLAGS += -DNDEBUG


#---------------------------------------------------------------------------
#
# Common warnings
#
#---------------------------------------------------------------------------
#-Wcast-qual
COMMON_WARNINGS = \
	-Wall \
	-Wextra \
	-Wpointer-arith \
	-Wshadow \
	-Wwrite-strings \
	-Wtrigraphs

#COMMON_C_WARNINGS = \
#	$(COMMON_WARNINGS) \
#	-Waggregate-return \
#	-Wstrict-prototypes \
#	-Wmissing-prototypes \
#	-Wmissing-declarations \
#	-Wnested-externs

COMMON_CXX_WARNINGS = \
	$(COMMON_WARNINGS)


#---------------------------------------------------------------------------
#
# x86_64 cflags
#
#---------------------------------------------------------------------------

# EZchip cflags
COMMON_EZCHIP_CFLAGS +=


#---------------------------------------------------------------------------
#
# Time mode
# make T=0|1
#    0 => no time (default)
#    1 => show time
#
#---------------------------------------------------------------------------

ifeq ("$(origin T)", "command line")
# To really make T go away in submakes, we have to override it.
override T:=$(T)
EZDK_TIME_LEVEL = $(T)
endif

ifndef EZDK_TIME_LEVEL
EZDK_TIME_LEVEL = 0
endif

ifeq ($(EZDK_TIME_LEVEL),0)
override COMMON_TIME=
else
override COMMON_TIME = TRUE
endif


#---------------------------------------------------------------------------
#
# Control plane flags
#
#---------------------------------------------------------------------------

# Control plane release flags
COMMON_CPE_RELEASE_OPT_LEVEL = -O2
COMMON_CPE_RELEASE_FLAGS = -DNDEBUG
COMMON_CPE_RELEASE_LOG_LEVEL = -DEZdevL_NOTE_LEVEL

# Control plane debug flags
COMMON_CPE_DEBUG_OPT_LEVEL = -O0
COMMON_CPE_DEBUG_FLAGS = -g
COMMON_CPE_DEBUG_LOG_LEVEL = -DEZdevL_MAINTENANCE_LEVEL

# Control plane warnings
COMMON_CPE_WARNINGS = \
	$(COMMON_C_WARNINGS) 
#	-Wdeclaration-after-statement



#---------------------------------------------------------------------------
#
# Linux flags
#
#---------------------------------------------------------------------------

# EZchip host cflags
COMMON_EZCHIP_CFLAGS += -DEZ_OS_LINUX_USER


#---------------------------------------------------------------------------
#
## Common commands
#
##---------------------------------------------------------------------------

# saved command line file name
common_cmd_file_name = $(dir $(1)).$(notdir $(1)).cmd

# gcc header depenedencies file name
common_dep_file_name = $(dir $(1)).$(notdir $(1)).d

# Makefile include files
common_include_cmd_files = $(wildcard $(foreach f,$(1),$(call common_cmd_file_name,$(f))))
common_include_dep_files = $(wildcard $(foreach f,$(1),$(call common_dep_file_name,$(f))))

# Recursive wildcard
common_rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call common_rwildcard,$d/,$2))

# _SCM_REV_ cpp flag
COMMON_SCM_CFLAG = -D_SCM_REV_=$(if $(EZDK_VERSION_ID),$(EZDK_VERSION_ID),local)

# Makefile clean files
common_clean_files = \
	$(strip \
		$(wildcard \
			$(foreach f,\
				$(1),\
				$(f) $(call common_cmd_file_name,$(f)) $(call common_dep_file_name,$(f))) \
		)\
	)

# Check if the invocation of make was with -B/--always-make
# this will force all special target to be rebuild
ifneq ($(filter -%B,$(MAKEFLAGS)),)
COMMON_FORCE_BUILD := 1
else
COMMON_FORCE_BUILD :=
endif

# Find any prerequisites that is newer than target
# Find any prerequisites that does not exists
# Find if the target itself doesnt exists
# Find if the target itself is a PHONY target
common_prereq_check = \
	$(filter-out $(COMMON_PHONY),$?) \
	$(filter-out $(COMMON_PHONY) $(wildcard $^),$^) \
	$(filter-out $(COMMON_PHONY) $(wildcard $@),$@) \
	$(filter $(COMMON_PHONY),$@) \
	$(COMMON_FORCE_BUILD)

# Check if the command line changed from previous build
common_cmd_check = \
	$(filter-out $(cmd_$@),$(cmd_$(1))) \
	$(filter-out $(cmd_$(1)),$(cmd_$@))

# Check if the command line changed from previous build
# while ignoring EZDK_PREFIX
common_no_ezdk_prefix = $(patsubst $(EZDK_PREFIX)%,%,$(1))
common_cmd_o_check = \
	$(filter-out $(cmd_$@),$(call common_no_ezdk_prefix,$(cmd_$(1)))) \
	$(filter-out $(call common_no_ezdk_prefix,$(cmd_$(1))),$(cmd_$@))

# Replace >$< with >$$< to preserve $ when reloading the .cmd file
# (needed for make)
# Replace >#< with >\#< to avoid starting a comment in the .cmd file
# (needed for make)
# Replace >'< with >'\''< to be able to enclose the whole string in '...'
# (needed for the shell
common_make_cmd = $(subst \#,\\\#,$(subst $$,$$$$,$(call escsq,$(cmd_$(1)))))

# Update gcc dependency file
# The problem is when the source file extention changes (e.g .c->.S)
# Make will exit with error because the old file doesnt exists
# And there is no target defining the old source file
# To resolve this we are removing the source file from object dependencies
common_update_dep_file = \
	sed -i \
	-e '1s|$@: \{1,\}$<|$@:|' \
	-e ':a;N;$$!ba;1,2s|$@: \{1,\}\\\n \{1,\}$<|$@:|' \
	$(call common_dep_file_name,$@)

common_o_rule = \
	$(if $(strip $(common_cmd_o_check) $(common_prereq_check)),\
		@set -e; \
		mkdir -p $(@D);	\
		$(o-pre-build-cmd) \
		echo 'cmd_$@ := $(call common_no_ezdk_prefix,$(common_make_cmd))' > $(call common_cmd_file_name,$@); \
		$(echo-cmd) \
		$(cmd_$(1)); \
		$(common_update_dep_file))

common_bin_rule = \
	$(if $(strip $(common_cmd_check) $(common_prereq_check)),\
		@set -e; \
		mkdir -p $(@D);	\
		rm -f $@; \
		echo 'cmd_$@ := $(common_make_cmd)' > $(call common_cmd_file_name,$@); \
		$(echo-cmd) \
		$(cmd_$(1)))

common_file_prereq_rule = \
	$(if $(strip $(common_prereq_check)),\
		@set -e; \
		$(echo-cmd) \
		$(cmd_$(1)))

common_general_rule = \
	$(if $(2),\
		@set -e; \
		$(echo-cmd) \
		$(cmd_$(1)))


#----------------------------------------------------
# Name:   common_cc_o_rule
# Desc:   compiltion of c file
#         should be used in makefile object file target
#         first dependency must be the c file
# Input:
#     1) compilation cflags
#----------------------------------------------------
common_cc_o_rule = $(call common_o_rule,cc_o,$(1))
quiet_cmd_cc_o = CC      $@
cmd_cc_o = $(CC) $(COMMON_CFLAGS) $(2) -c -o $@ $<
	

#----------------------------------------------------
# Name:   common_asm_o_rule
# Desc:   compiltion of asm file
#         should be used in makefile object file target
#         first dependency must be the asm file
# Input:
#         1) compilation cflags
#----------------------------------------------------
common_asm_o_rule = $(call common_o_rule,asm_o,$(1))
quiet_cmd_asm_o = AS      $@
cmd_asm_o = $(CC_NO_PREFIX) $(COMMON_CFLAGS) $(2) -c -o $@ $<


#----------------------------------------------------
# Name:   common_cxx_o_rule
# Desc:   compiltion of cpp file
#         should be used in makefile object file target
#         first dependency must be the cpp file
# Input:
#         1) compilation cxxflags
#----------------------------------------------------
common_cxx_o_rule = $(call common_o_rule,cxx_o,$(1))
quiet_cmd_cxx_o = CXX     $@
cmd_cxx_o = $(CXX) $(COMMON_CFLAGS) $(2) -c -o $@ $<


#----------------------------------------------------
# Name:   common_static_lib_rule
# Desc:   create static archive library
#         should be used in static archive library target
#         the makefile target dependencies will be in the archive
#----------------------------------------------------
common_static_lib_rule = $(call common_bin_rule,static_lib)
quiet_cmd_static_lib = AR      $@
cmd_static_lib = $(AR) rcs $@ $(filter-out $(COMMON_PHONY),$^)


#----------------------------------------------------
# Name:   common_shared_lib_rule
# Desc:   create shared archive library
#         should be used in shared archive library target
#         the makefile target dependencies will be in the archive
#----------------------------------------------------
common_shared_lib_rule = $(call common_bin_rule,shared_lib,$(1),$(2))
quiet_cmd_shared_lib = LD      $@
cmd_shared_lib = $(LD) -Wl,-soname,$(notdir $@) -shared -fPIC -o $@ \
		-Wl,-whole-archive $(filter-out $(COMMON_PHONY),$^) -Wl,-no-whole-archive


#----------------------------------------------------
# Name:   common_cc_ld_rule
# Desc:   create ELF using $(CC)
#         should be used in ELF file target
# Input:
#         1) objects
#         2) LDFLAGS
#----------------------------------------------------
ifeq ("$(origin M)", "command line")
COMMON_MODPOST_ENABLED = $(M)
endif

ifndef COMMON_MODPOST_ENABLED
COMMON_MODPOST_ENABLED = 0
endif

common_cc_ld_rule = $(call common_bin_rule,cc_ld,$(1),$(2),$(3))
quiet_cmd_cc_ld = LD      $@
ifeq ($(COMMON_MODPOST_ENABLED),0)
cmd_cc_ld = $(LD) $(2) $(COMMON_LDFLAGS) $(3) -o $@
else ifeq ($(COMMON_MODPOST_ENABLED),1)
ifneq (,$(findstring linux_arc,linux_x86_64))
cmd_cc_ld = $(CROSS_COMPILE)ld $(filter-out -pthread -lm,$(2) $(COMMON_LDFLAGS) $(3)) -r -EB -o $(dir $@)/built-in.o; \
        $(if $(4),$(EZDK_LDK_DIR)/toolchain/bin/EZmodpost -p $(4) $(dir $@)/built-in.o,$(EZDK_LDK_DIR)/toolchain/bin/EZmodpost $(dir $@)/built-in.o); \
        $(LD) $(2) $(COMMON_LDFLAGS) $(3) -o $@
else
cmd_cc_ld = $(LD) $(2) $(COMMON_LDFLAGS) $(3) -o $@
endif
endif

#----------------------------------------------------
# Name:   common_rec_cc_ld_rule
# Desc:   create ELF using $(CC) with --start-group and --end-group flags
#         in order to solve dependencies between objects
#         should be used in ELF file target
# Input:
#         1) objects
#         2) LDFLAGS
#----------------------------------------------------
ifeq ("$(origin M)", "command line")
COMMON_MODPOST_ENABLED = $(M)
endif

ifndef COMMON_MODPOST_ENABLED
COMMON_MODPOST_ENABLED = 0
endif

common_rec_cc_ld_rule = $(call common_bin_rule,rec_cc_ld,$(1),$(2),$(3))
quiet_cmd_rec_cc_ld = LD      $@
ifeq ($(COMMON_MODPOST_ENABLED),0)
cmd_rec_cc_ld = $(LD) -Wl,--start-group $(2) -Wl,--end-group $(COMMON_LDFLAGS) $(3) -o $@
else ifeq ($(COMMON_MODPOST_ENABLED),1)
ifneq (,$(findstring linux_arc,linux_x86_64))
cmd_rec_cc_ld = $(CROSS_COMPILE)ld $(filter-out -pthread -lm,$(2) $(COMMON_LDFLAGS) $(3)) -r -EB -o $(dir $@)/built-in.o; \
	$(if $(4),$(EZDK_LDK_DIR)/toolchain/bin/EZmodpost -p $(4) $(dir $@)/built-in.o,$(EZDK_LDK_DIR)/toolchain/bin/EZmodpost $(dir $@)/built-in.o); \
	$(LD) -Wl,--start-group $(2) -Wl,--end-group $(COMMON_LDFLAGS) $(3) -o $@
else
cmd_rec_cc_ld = $(LD) -Wl,--start-group $(2) -Wl,--end-group $(COMMON_LDFLAGS) $(3) -o $@
endif
endif

#----------------------------------------------------
# Name:   common_cxx_ld_rule
# Desc:   create ELF using $(CXX)
#         should be used in ELF file target
# Input:
#         1) objects
#         2) LDFLAGS
#----------------------------------------------------
common_cxx_ld_rule = $(call common_bin_rule,cxx_ld,$(1),$(2))
quiet_cmd_cxx_ld = LD      $@
cmd_cxx_ld = $(CXXLD) $(2) $(COMMON_LDFLAGS) $(3) -o $@


#----------------------------------------------------
# Name:   common_rec_cxx_ld_rule
# Desc:   create ELF using $(CXX) with --start-group and --end-group flags
#         in order to solve dependencies between objects
#         should be used in ELF file target
# Input:
#         1) objects
#         2) LDFLAGS
#----------------------------------------------------
common_rec_cxx_ld_rule = $(call common_bin_rule,rec_cxx_ld,$(1),$(2))
quiet_cmd_rec_cxx_ld = LD      $@
cmd_rec_cxx_ld = $(CXXLD) -Wl,--start-group $(2) -Wl,--end-group $(COMMON_LDFLAGS) $(3) -o $@


#----------------------------------------------------
# Name:   common_objdump_rule
# Desc:   create dissasmebly file from ELF file
#         should be used in makefile dissasmebly file target
#         the first dependency of the target should be the ELF file
# Input:
#         1) objdump flags (default is -S -d)
#----------------------------------------------------
common_objdump_rule = $(call common_bin_rule,objdump,$(1))
quiet_cmd_objdump = OBJDUMP $@
cmd_objdump = $(OBJDUMP) $(if $(2),$(2),-S -d) $< > $@


#----------------------------------------------------
# Name:   common_objcopy_rule
# Desc:   run objcopy on ELF file
#         should be used in makefile file target
#         the first dependency of the target should be the ELF file
# Input:
#         1) objcopy flags (default is -S -O binary)
#----------------------------------------------------
common_objcopy_rule = $(call common_bin_rule,objcopy,$(1))
quiet_cmd_objcopy = OBJCOPY $@
cmd_objcopy = $(OBJCOPY) $(if $(2),$(2),-S -O binary) $< $@


#----------------------------------------------------
# Name:   common_copy_file_rule
# Desc:   copy input file to output file
# Input:  
#         1) input file
#         2) output file
#----------------------------------------------------
common_copy_file_rule = $(call common_file_prereq_rule,copy_file,$(1),$(2))
quiet_cmd_copy_file = CP      $(2) $(3)
cmd_copy_file = mkdir -p $(dir $(3)); cp -f $(2) $(3)


#----------------------------------------------------
# Name:   common_copy_folder_rule
# Desc:   sync input folder to output folder
# Input:  
#         1) input folder
#         2) output folder
#         3) list of excluded files
#----------------------------------------------------
common_copy_folder_rule = $(call common_general_rule,copy_folder,1,$(1),$(2),$(3))
quiet_cmd_copy_folder = RSYNC   $(3) $(4)
cmd_copy_folder = mkdir -p $(dir $(4)); \
		rsync -au $(foreach file,$(5) .git .svn,--exclude=$(file)) $(3)/ $(4)


#----------------------------------------------------
# Name:   common_create_file_rule
# Desc:   run a general command to create a file
# Input:
#         1) command to create the file
#----------------------------------------------------
common_create_file_rule = $(call common_file_prereq_rule,create_file,$(1))
quiet_cmd_create_file = GEN     $@
cmd_create_file = mkdir -p $(@D); $(2)


#----------------------------------------------------
# Name:   common_create_file_check_rule
# Desc:   run a general command to create a file if command changed from previous run
# Input:
#         1) command to create the file
#----------------------------------------------------
common_create_file_check_rule = $(call common_bin_rule,create_file_check,$(1))
quiet_cmd_create_file_check = GEN     $@
cmd_create_file_check = $(2)


#----------------------------------------------------
# Name:   common_clean_rule
# Desc:   delete input files listed, dependency files, cmd files
# Input:
#         1) list of files to be removed
#----------------------------------------------------
common_clean_rule = $(call common_general_rule,clean,$(call common_clean_files,$(1)))
quiet_cmd_clean = CLEAN   $(@:%-clean=%-$(COMMON_PLATFORM))
cmd_clean = rm -f $(2)


#----------------------------------------------------
# Name:   common_clean_folder_rule
# Desc:   delete input folders liste
# Input:
#         1) list of folders to be removed
#----------------------------------------------------
common_clean_folder_rule = $(call common_general_rule,fclean,$(wildcard $(1)))
quiet_cmd_fclean = CLEAN   $(@:%-clean=%)
cmd_fclean = rm -rf $(2)


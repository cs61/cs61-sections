# compiler flags
CFLAGS := -std=gnu11 -Wall -Wextra -Wshadow -g $(DEFS) $(CFLAGS)
CXXFLAGS := -std=gnu++2a -Wall -Wextra -Wshadow -g $(DEFS) $(CXXFLAGS)

O ?= -O3
ifeq ($(filter 0 1 2 3 s z g fast,$(O)),$(strip $(O)))
override O := -O$(O)
endif

PTHREAD ?= 0
ifeq ($(PTHREAD),1)
CFLAGS += -pthread
CXXFLAGS += -pthread
WANT_TSAN ?= 1
endif

PIE ?= 1
ifeq ($(PIE),0)
LDFLAGS += -no-pie
endif

# compiler variant
ifeq ($(COMPILER),clang)
 ifeq ($(origin CC),default)
  ifeq ($(shell if clang --version | grep -e 'LLVM\|clang' >/dev/null; then echo 1; else echo 0; fi),1)
CC = clang
  endif
 endif
 ifeq ($(origin CXX),default)
  ifeq ($(shell if clang++ --version | grep -e 'LLVM\|clang' >/dev/null; then echo 1; else echo 0; fi),1)
CXX = clang++
  endif
 endif
endif
ifeq ($(COMPILER),gcc)
 ifeq ($(origin CC),default)
  ifeq ($(shell if gcc --version 2>&1 | grep -e 'Free Software' >/dev/null; then echo 1; else echo 0; fi),1)
CC = gcc
  endif
 endif
 ifeq ($(origin CXX),default)
  ifeq ($(shell if g++ --version 2>&1 | grep -e 'Free Software' >/dev/null; then echo 1; else echo 0; fi),1)
CXX = g++
  endif
 endif
endif

ISCLANG := $(shell if $(CC) --version | grep -e 'LLVM\|clang' >/dev/null; then echo 1; else echo 0; fi)
ifeq ($(ISCLANG),1)
BADCXXFLAGS ?= -fno-if-conversion -fno-if-conversion2
endif

ifeq ($(NEED_CXX_GCC),1)
GXX_ISCLANG := $(shell if g++ --version | grep -e 'LLVM\|clang' >/dev/null; then echo 1; else echo 0; fi)
 ifeq ($(GXX_ISCLANG),1)
  ifeq ($(shell if g++-12 --version 2>/dev/null | grep -e 'Free Software' >/dev/null; then echo 1; else echo 0; fi),1)
CXX_GCC = g++-12
  else ifeq ($(shell if g++-11 --version 2>/dev/null | grep -e 'Free Software' >/dev/null; then echo 1; else echo 0; fi),1)
CXX_GCC = g++-11
  else ifeq ($(shell if g++-10 --version 2>/dev/null | grep -e 'Free Software' >/dev/null; then echo 1; else echo 0; fi),1)
CXX_GCC = g++-10
  else
CXX_GCC = false
  endif
 else
CXX_GCC = g++
 endif
endif

# sanitizer arguments
ifndef SAN
SAN := $(SANITIZE)
endif
ifeq ($(SAN),1)
 ifndef ASAN
ASAN := $(if $(strip $(shell $(CC) -v 2>&1 | grep 'build=aarch.*target=x86')),,1)
 endif
endif
ifndef TSAN
 ifeq ($(WANT_TSAN),1)
TSAN := $(SAN)
 endif
endif

check_for_sanitizer = $(if $(strip $(shell $(CC) -fsanitize=$(1) -x c -E /dev/null 2>&1 | grep sanitize=)),$(info ** WARNING: The `$(CC)` compiler does not support `-fsanitize=$(1)`.),1)
ifeq ($(TSAN),1)
 ifeq ($(call check_for_sanitizer,thread),1)
CFLAGS += -fsanitize=thread
CXXFLAGS += -fsanitize=thread
 endif
else
 ifeq ($(or $(ASAN),$(LSAN),$(LEAKSAN)),1)
  ifeq ($(call check_for_sanitizer,address),1)
CFLAGS += -fsanitize=address
CXXFLAGS += -fsanitize=address
  endif
 endif
 ifeq ($(or $(LSAN),$(LEAKSAN)),1)
  ifeq ($(call check_for_sanitizer,leak),1)
CFLAGS += -fsanitize=leak
CXXFLAGS += -fsanitize=leak
  endif
 endif
endif
ifeq ($(or $(UBSAN),$(SAN)),1)
 ifeq ($(call check_for_sanitizer,undefined),1)
CFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined
CXXFLAGS += -fsanitize=undefined -fno-sanitize-recover=undefined
 endif
endif

# profiling
ifeq ($(or $(PROFILE),$(PG)),1)
CFLAGS += -pg
CXXFLAGS += -pg
endif

# these rules ensure dependencies are created
DEPCFLAGS = -MD -MF $(DEPSDIR)/$(patsubst %.o,%,$(@F)).d -MP
DEPSDIR := .deps
BUILDSTAMP := $(DEPSDIR)/rebuildstamp
DEPFILES := $(wildcard $(DEPSDIR)/*.d)
ifneq ($(DEPFILES),)
include $(DEPFILES)
endif

# when the C compiler or optimization flags change, rebuild all objects
ifneq ($(strip $(DEP_CC)),$(strip $(CC) $(CPPFLAGS) $(CFLAGS) $(O)))
DEP_CC := $(shell mkdir -p $(DEPSDIR); echo >$(BUILDSTAMP); echo "DEP_CC:=$(CC) $(CPPFLAGS) $(CFLAGS) $(O)" >$(DEPSDIR)/_cc.d)
endif
ifneq ($(strip $(DEP_CXX)),$(strip $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(O) $(LDFLAGS)))
DEP_CXX := $(shell mkdir -p $(DEPSDIR); echo >$(BUILDSTAMP); echo "DEP_CXX:=$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(O) $(LDFLAGS)" >$(DEPSDIR)/_cxx.d)
endif


V = 0
ifeq ($(V),1)
run = $(1) $(3)
xrun = /bin/echo "$(1) $(3)" && $(1) $(3)
else
run = @$(if $(2),/bin/echo "  $(2) $(3)" &&,) $(1) $(3)
xrun = $(if $(2),/bin/echo "  $(2) $(3)" &&,) $(1) $(3)
endif
runquiet = @$(1) $(3)

CXX_LINK_PREREQUISITES = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

CLEANASM = 1
ifeq ($(CLEANASM),1)
cleanasm = perl -ni -e '$$badsection = !!/\.note\.gnu/ if /^\s+\.section/; print if !/^(?:\# BB|\s+\.cfi|\s+\.p2align|\s+\.loc|\.LF[BE]|\.LVL|\s+\# =>This|\s+\# kill)/ && !$$badsection' $(1)
else
cleanasm = :
endif

DEFAULT_ASM_CXXFLAGS ?= $(O)
flagged_compile = @ARGS=$$(grep '^//!' $< | sed 's/.*!//$(patsubst %,;s/ % */ /,$(BADCXXFLAGS));s/^ | $$//'); \
	  if test -z "$$ARGS"; then ARGS="$(DEFAULT_ASM_CXXFLAGS)"; fi; \
	  $(call xrun,$(CXX) $(3) $$ARGS -o $(2) $(1),COMPILE $$ARGS $(1) -o $(2))
flagged_compile_S = $(call flagged_compile,$(1),$(2),$(filter-out -g,$(3) -S)) && { $(call cleanasm,$(2)); }
flagged_compile_c = $(call flagged_compile,$(1),$(2),$(3) -c)


PERCENT := %

# cancel implicit rules we don't want
%: %.c
%.o: %.c
%: %.cc
%.o: %.cc
%: %.o
%.o: %.s

$(BUILDSTAMP):
	@mkdir -p $(@D)
	@echo >$@

always:
	@:

clean-hook:
	@:

.PHONY: always clean-hook
.PRECIOUS: %.o

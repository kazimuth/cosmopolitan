#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘
#
# OVERVIEW
#
#   αcτµαlly pδrταblε εxεcµταblε
#
# DESCRIPTION
#
#   This file defines the libraries, runtimes, and build rules needed to
#   create executables from your Linux workstation that'll run anywhere.
#   Loading this package will make certain systemic modifications to the
#   build like turning off the System V "Red Zone" optimization, because
#   αcτµαlly pδrταblε εxεcµταblεs need to be able to run in kernelspace.

PKGS += APE

DEFAULT_COPTS += -mno-red-zone
DEFAULT_LDFLAGS += -z max-page-size=0x1000

APELINK = ACTION=LINK.ape $(LINK) $(LINKARGS) $(OUTPUT_OPTION) && $(STRIP) -X $@ && $(GZ) $(ZFLAGS) -f $@.map

APE =	$(APE_DEPS)			\
	$(APE_OBJS)			\
	o/$(MODE)/ape/ape.lds

APE_FILES :=				\
	$(wildcard ape/*.*)

APE_HDRS =				\
	$(filter %.h,$(APE_FILES))

APE_SRCS =				\
	$(filter %.S,$(APE_FILES))

APE_OBJS =				\
	$(APE_SRCS:%=o/$(MODE)/%.zip.o)	\
	$(APE_SRCS:%.S=o/$(MODE)/%.o)

APE_DEPS =				\
	$(APE_LIB)

APE_CHECKS =				\
	$(APE_HDRS:%=o/%.ok)

o/%.com: o/%.com.dbg
	@ACTION=OBJCOPY.ape TARGET=$@ build/do $(OBJCOPY) -SO binary $< $@

o/ape/idata.inc: ape/idata.h ape/relocations.h

$(APE_OBJS):	$(BUILD_FILES)		\
		ape/ape.mk

.PHONY: o/$(MODE)/ape
o/$(MODE)/ape:	$(APE)			\
		$(APE_CHECKS)		\
		o/$(MODE)/ape/lib

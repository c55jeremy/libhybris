bionic = $(top_srcdir)/common/p/codebase/bionic
bionic_libc = $(bionic)/libc
system = $(top_srcdir)/common/p/codebase/system
system_base = $(system)/core/base/include

modlibexecdir = $(libdir)/libhybris/linker
modlibexec_LTLIBRARIES = p.la

ARCH_FLAGS =

AM_CFLAGS = \
	-std=gnu99

AM_CPPFLAGS = \
	-fno-stack-protector \
	-Wstrict-overflow=5

AM_CXXFLAGS = \
	-std=gnu++11 \
	-Wold-style-cast

##	hybris_compat.cpp \
## linker_allocator.cpp \
## linker_memory.cpp \

p_la_SOURCES = \
	dlfcn.cpp \
	linker_block_allocator.cpp \
	linker_cfi.cpp \
	linker_config.cpp \
	linker_dlwarning.cpp \
	linker_gdb_support.cpp \
	linker_globals.cpp \
	linker_logger.cpp \
	linker_main.cpp \
	linker_mapped_file_fragment.cpp \
	linker_namespaces.cpp \
	linker_phdr.cpp \
	linker_sdk_versions.cpp \
	linker_soinfo.cpp \
	linker_utils.cpp \
	linker.cpp \
	rt.cpp \
	compat/ScopedTrace.cpp \
	compat/async_safe_log.cpp \
	compat/stringl.c \
	codebase/system/core/base/file.cpp \
	codebase/system/core/base/strings.cpp \
	codebase/system/core/base/stringprintf.cpp 
	
##	 \
##	../strlcpy.c \
##	../strlcat.c
	
p_la_CPPFLAGS = \
	-DHYBRIS_ENABLED=1 \
	-D__ANDROID_API__=28 \
	$(AM_CPPFLAGS) \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(bionic_libc)/ \
	-I$(bionic_libc)/include \
	-I$(system_base) \
	-DDEFAULT_HYBRIS_LD_LIBRARY_PATH="\"@DEFAULT_HYBRIS_LD_LIBRARY_PATH@\"" \
	$(ARCH_FLAGS) \
	$(ANDROID_HEADERS_CFLAGS)
	
p_la_LDFLAGS = \
    -shared \
	-lsupc++ \
	-module \
	-avoid-version

if WANT_DEBUG
p_la_CPPFLAGS += \
	-DTRACE_DEBUG=1
else
p_la_CPPFLAGS += \
	-DTRACE_DEBUG=1
endif

if WANT_ARM_TRACING
p_la_CPPFLAGS += \
	-DWANT_ARM_TRACING
endif


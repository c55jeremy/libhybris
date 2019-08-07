lib_LTLIBRARIES = \
    libcutils.la

libcutils_la_SOURCES = \
    native_handle.cpp \
    ashmem-dev.cpp \
    stringl.cpp \
    threads.cpp

libcutils_la_CXXFLAGS = -std=gnu++14 -fPIC -D__HYBRIS__ -D__ANDROID__ -DANDROID

libcutils_la_CXXFLAGS += \
    -I$(top_srcdir)/include/android/external/safe_iop/include \
    -I$(top_srcdir)/include/android/system/core/libutils/include \
    -I$(top_srcdir)/include/android/system/core/base/include \
    -I$(top_srcdir)/include/android/system/core/libbacktrace/include

libcutils_la_LDFLAGS = \
	-ldl

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cutils.pc
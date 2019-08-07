lib_LTLIBRARIES = \
    libutils.la

libutils_la_SOURCES = \
    misc.cpp \
    Printer.cpp \
    RefBase.cpp \
    SharedBuffer.cpp \
    Static.cpp \
    String8.cpp \
    String16.cpp \
    StrongPointer.cpp \
    SystemClock.cpp \
    Threads.cpp \
    Timers.cpp \
    VectorImpl.cpp  \
    Unicode.cpp \
    android_log.cpp \
    stringprintf.cpp

libutils_la_CXXFLAGS = -std=gnu++14 -fPIC -D__HYBRIS__

libutils_la_CXXFLAGS += \
    -I$(top_srcdir)/include/android/external/safe_iop/include \
    -I$(top_srcdir)/include/android/system/core/libutils/include \
    -I$(top_srcdir)/include/android/system/core/base/include \
    -I$(top_srcdir)/include/android/system/core/libbacktrace/include

libutils_la_LDFLAGS = \
	-ldl

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = utils.pc
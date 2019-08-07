SUBDIRS = libcutils libutils

lib_LTLIBRARIES = \
    libbinder.la

libbinder_la_SOURCES = \
    Binder.cpp \
    BpBinder.cpp \
    BufferedTextOutput.cpp \
    Debug.cpp \
    IInterface.cpp \
    IMemory.cpp \
    IPCThreadState.cpp \
    IResultReceiver.cpp \
    IServiceManager.cpp \
    IShellCallback.cpp \
    MemoryBase.cpp \
    MemoryDealer.cpp \
    MemoryHeapBase.cpp \
    Parcel.cpp \
    PersistableBundle.cpp \
    ProcessState.cpp \
    Static.cpp \
    Status.cpp \
    TextOutput.cpp \
    IPermissionController.cpp \
    Value.cpp

libbinder_la_CXXFLAGS = -std=gnu++14 -fPIC -D__HYBRIS__ -D__ANDROID__ -DANDROID

libbinder_la_CXXFLAGS += \
    -pthread \
    -I$(top_srcdir)/include/android/system/core/libutils/include \
    -I$(top_srcdir)/include/android/system/core/base/include \
    -I$(top_srcdir)/include/android/frameworks/native/libs/binder/include \
    -I$(top_srcdir)/include/android/system/core/libbacktrace/include
    
libbinder_la_LDFLAGS =  \
    -lsupc++ \
    -lpthread \
    -version-info "1":"0":"0"

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = binder.pc
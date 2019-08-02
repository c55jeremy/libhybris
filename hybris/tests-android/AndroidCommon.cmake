#Android P Codebase (AOSP) 預設編譯
#確保Android Build環境完整!
if ($ENV{ANDROID_BUILD_TOP} STREQUAL "")
  message(FATAL_ERROR "Please make sure Android Build environment is setup!")
else()
  message(STATUS "Android codebase in " $ENV{ANDROID_BUILD_TOP})
endif()

#設定CROSS Compile
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SKIP_BUILD_RPATH TRUE) #解決DT_RPATH unused的警告，這是由linker發出

#設定C/C++ Compiler
if(USE_CLANG)
# CLANG from soong/cc/config/global.go:	ClangDefaultVersion = "clang-4691093"
  set(CLANG_VERSION "4691093")
  set(CMAKE_CXX_COMPILER $ENV{ANDROID_BUILD_TOP}/prebuilts/clang/host/linux-x86/clang-${CLANG_VERSION}/bin/clang++)
  set(CMAKE_C_COMPILER $ENV{ANDROID_BUILD_TOP}/prebuilts/clang/host/linux-x86/clang-${CLANG_VERSION}/bin/clang)
  set(ANDROID_CLANG_TARGET_FLAGS "-target aarch64-linux-android -B$ENV{ANDROID_TOOLCHAIN}") #Clang需要
else()
# GCC
  set(CMAKE_CXX_COMPILER $ENV{ANDROID_TOOLCHAIN}/aarch64-linux-android-g++)
  set(CMAKE_C_COMPILER $ENV{ANDROID_TOOLCHAIN}/aarch64-linux-android-gcc)
endif()

#設定通用Definitions
add_definitions(
  -DANDROID
  -D_FORTIFY_SOURCE=2 
  -D__compiler_offsetof=__builtin_offsetof 
  -D_USING_LIBCXX 
  -D_LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS)

#設定通用Compile C/C++ Flags
set(CMAKE_COMMON_FLAGS "-Wall -fmessage-length=0 ${ANDROID_CLANG_TARGET_FLAGS}")
#set(CMAKE_COMMON_FLAGS "-Wall -fmessage-length=0 -xxx")
set(CMAKE_C_FLAGS "${CMAKE_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_COMMON_FLAGS}")

#設定通用Include Path
include_directories(
  $ENV{ANDROID_BUILD_TOP}/external/libcxx/include
  $ENV{ANDROID_BUILD_TOP}/external/libcxxabi/include
  $ENV{ANDROID_BUILD_TOP}/bionic/libc/kernel/uapi/asm-arm64
  $ENV{ANDROID_BUILD_TOP}/bionic/libc/include
  $ENV{ANDROID_BUILD_TOP}/bionic/libc/kernel/uapi
  $ENV{ANDROID_BUILD_TOP}/bionic/libc/kernel/android/uapi
)

#設定連結Flags及函式庫變數
set(ANDROID_LINK_FLAGS64 "-pie -nostdlib -Bdynamic -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,-dynamic-linker,/system/bin/linker64 -Wl,-rpath-link=$ENV{ANDROID_PRODUCT_OUT}/obj/lib")
set(ANDROID_RPATH "-Wl,--rpath=/system/lib64") #目前用不上
set(ANDROID_SHAREDLIB_LINK_FLAGS "-nostdlib -shared  -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--build-id=md5 -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,-maarch64linux -Wl,--hash-style=gnu -Wl,--fix-cortex-a53-843419 -fuse-ld=gold -Wl,--icf=safe -Wl,--no-undefined-version")
set(ANDROID_COMMON_STATIC_LIBS64 "-Wl,--whole-archive -Wl,--no-whole-archive $ENV{ANDROID_PRODUCT_OUT}/obj/STATIC_LIBRARIES/libcompiler_rt-extras_intermediates/libcompiler_rt-extras.a $ENV{ANDROID_PRODUCT_OUT}/obj/STATIC_LIBRARIES//libatomic_intermediates/libatomic.a $ENV{ANDROID_PRODUCT_OUT}/obj/STATIC_LIBRARIES/libgcc_intermediates/libgcc.a")
#執行檔CRT
set(ANDROID_CRTBEDING_DYNAMIC64 "$ENV{ANDROID_PRODUCT_OUT}/obj/lib/crtbegin_dynamic.o")
set(ANDROID_CRTEND_ANDROID64 "$ENV{ANDROID_PRODUCT_OUT}/obj/lib/crtend_android.o")
#動態連結檔CRT
set(ANDROID_CRTBEDING_SO64 "$ENV{ANDROID_PRODUCT_OUT}/obj/lib/crtbegin_so.o")
set(ANDROID_CRTEND64 "$ENV{ANDROID_PRODUCT_OUT}/obj/lib/crtend_so.o")
#系統函式庫
link_directories($ENV{ANDROID_PRODUCT_OUT}/system/lib64)
set(ANDROID_COMMON_SHARED_LIBS64 "$ENV{ANDROID_PRODUCT_OUT}/system/lib64/ld-android.so")
set(ANDROID_SYSTEM_SHARED_LIBS64 "-Wl,--no-undefined $ENV{ANDROID_PRODUCT_OUT}/obj/lib/libc++.so $ENV{ANDROID_PRODUCT_OUT}/obj/lib/libc.so $ENV{ANDROID_PRODUCT_OUT}/obj/lib/libm.so $ENV{ANDROID_PRODUCT_OUT}/obj/lib/libdl.so")
#整合以上變數，產生Linker Flags
set(CMAKE_EXE_LINKER_FLAGS "${ANDROID_LINK_FLAGS64} ${ANDROID_CLANG_TARGET_FLAGS} ${ANDROID_COMMON_STATIC_LIBS64} ${ANDROID_COMMON_SHARED_LIBS64} ${ANDROID_CRTBEDING_DYNAMIC64} ${ANDROID_CRTEND_ANDROID64}")
set(CMAKE_SHARED_LINKER_FLAGS "${ANDROID_SHAREDLIB_LINK_FLAGS} ${ANDROID_CLANG_TARGET_FLAGS} ${ANDROID_COMMON_STATIC_LIBS64} ${ANDROID_SYSTEM_SHARED_LIBS64} ${ANDROID_CRTBEDING_SO64} ${ANDROID_CRTEND64}")

/*
 * Copyright (C) 2019 The Duoplex Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#pragma once
#include <stddef.h>
#include <string.h>
#include <elf.h>

#include "android/api-level.h"

/***From Bionic cdefs.h***/
#define __INTRODUCED_IN(api_level) __attribute__((annotate("introduced_in=" #api_level)))
#define __LIBC_HIDDEN__ __attribute__((visibility("hidden")))
#define __unused __attribute__((__unused__))
#define __printflike(x, y) __attribute__((__format__(printf, x, y)))
#define	__predict_false(exp)	__builtin_expect((exp) != 0, 0)
#define	__predict_true(exp)	__builtin_expect((exp) != 0, 1)

/***From Bionic sys/usre.h***/
#define PAGE_SIZE 4096
/***From Boinic string.h***/
#ifdef __cplusplus
extern "C" {
#endif
extern size_t strlcat(char* __dst, const char* __src, size_t __n);
extern size_t strlcpy(char* __dst, const char* __src, size_t __n);
extern uint32_t arc4random_uniform(uint32_t upper_bound);
extern void arc4random_buf(void* __buf, size_t __n);

// stubbed for hybris support:
static inline void bionic_trace_begin(const char* message) {};
static inline void bionic_trace_end() {};

#ifdef __cplusplus
}
#endif
/***From Bionic elf.h***/
/* Relocation table entry for relative (in section of type SHT_RELR). */
#define ELF_ST_BIND(x) ((x) >> 4)
#define ELF_ST_TYPE(x) ((x) & 0xf)

#define DT_ANDROID_REL (DT_LOOS + 2)
#define DT_ANDROID_RELSZ (DT_LOOS + 3)
#define DT_ANDROID_RELA (DT_LOOS + 4)
#define DT_ANDROID_RELASZ (DT_LOOS + 5)
#define DT_RELR 0x6fffe000
#define DT_RELRSZ 0x6fffe001
#define DT_RELRENT 0x6fffe003
#define DT_RELRCOUNT 0x6fffe005

typedef Elf32_Word Elf32_Relr;
typedef Elf64_Xword Elf64_Relr;

/***From Bionic pthread.h***/
typedef void (*__pthread_cleanup_func_t)(void*);

typedef struct __pthread_cleanup_t {
  struct __pthread_cleanup_t*   __cleanup_prev;
  __pthread_cleanup_func_t      __cleanup_routine;
  void*                         __cleanup_arg;
} __pthread_cleanup_t;

/*** From kernel/uapi/linux/magic.h***/
#define TMPFS_MAGIC 0x01021994
#define DF_1_PIE        0x08000000
#define PATH_MAX 4096
#define PAGE_MASK (~(PAGE_SIZE - 1))

/***Fix Duplicated inline***/
//#ifdef __always_inline
//#undef __always_inline
//#define	__always_inline
//#endif

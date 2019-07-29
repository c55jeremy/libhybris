/*
 * bionic_arc4random.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jeremychen
 */


#include "private/bionic_arc4random.h"

#include <stdlib.h>
#include <string.h>
#include <sys/auxv.h>
#include <unistd.h>

#include <async_safe/log.h>

#include "private/KernelArgumentBlock.h"

extern void arc4random_buf(void* __buf, size_t __n);

void __libc_safe_arc4random_buf(void* buf, size_t n, KernelArgumentBlock& args) {
  // Only call arc4random_buf once we have `/dev/urandom` because getentropy(3)
  // will fall back to using `/dev/urandom` if getrandom(2) fails, and abort if
  // if can't use `/dev/urandom`.
  static bool have_urandom = access("/dev/urandom", R_OK) == 0;
  if (have_urandom) {
    arc4random_buf(buf, n);
    return;
  }

  static size_t at_random_bytes_consumed = 0;
  if (at_random_bytes_consumed + n > 16) {
    async_safe_fatal("ran out of AT_RANDOM bytes, have %zu, requested %zu",
                     16 - at_random_bytes_consumed, n);
  }

  memcpy(buf, reinterpret_cast<char*>(args.getauxval(AT_RANDOM)) + at_random_bytes_consumed, n);
  at_random_bytes_consumed += n;
  return;
}

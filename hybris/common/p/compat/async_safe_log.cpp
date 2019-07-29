/*
 * async_safe_log.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jeremychen
 */
#include <stdio.h>
#include <stdarg.h>

#include "async_safe/log.h"



int async_safe_write_log(int priority, const char* tag, const char* msg) {
	printf("async_safe_write_log:\n");
	//vprintf(format, args);
	//printf("!!!\n");
  return 0;
}

int async_safe_format_log_va_list(int priority, const char* tag, const char* format, va_list args) {
  char buffer[1024];

	printf("async_safe_format_log_va_list:\n");
//	vprintf(format, args);
//	printf("!!!\n");

  return async_safe_write_log(priority, tag, buffer);
}

void async_safe_fatal_va_list(const char* prefix, const char* format, va_list args) {
  char msg[1024];
  async_safe_write_log(ANDROID_LOG_FATAL, "libc", msg);
}

void async_safe_fatal_no_abort(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  async_safe_fatal_va_list(nullptr, fmt, args);
  va_end(args);
}

int async_safe_format_fd(int fd, const char* format, ...) {
  va_list args;
  va_start(args, format);
  async_safe_fatal_va_list(nullptr, format, args);
  va_end(args);
  return 0;
}

int async_safe_format_buffer_va_list(char* buffer, size_t buffer_size, const char* format,                                     va_list args) {
  return vsnprintf(buffer, buffer_size, format, args);
}

int async_safe_format_log(int priority, const char* tag, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int result = async_safe_format_log_va_list(priority, tag, format, args);
  va_end(args);
  return result;
}

int async_safe_format_buffer(char* buffer, size_t buffer_size, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int buffer_len = async_safe_format_buffer_va_list(buffer, buffer_size, format, args);
  va_end(args);
  return buffer_len;
}

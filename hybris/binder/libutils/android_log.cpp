/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#include "log_fake.h"
#include <iostream>
#include <string>

#include <errno.h>
#include <stdarg.h>

#include <string>

#include <android-base/stringprintf.h>
#include <log/log.h>

// Forward declarations.
class Backtrace;
struct EventTagMap;
struct AndroidLogEntry;

std::string g_fake_log_buf;

std::string g_fake_log_print;


void resetLogs();
std::string getFakeLogBuf();
std::string getFakeLogPrint();

void resetLogs() {
  g_fake_log_buf = "";
  g_fake_log_print = "";
}

std::string getFakeLogBuf() {
  return g_fake_log_buf;
}

std::string getFakeLogPrint() {
  return g_fake_log_print;
}

extern "C" int __android_log_buf_write(int bufId, int prio, const char* tag, const char* msg) {
  g_fake_log_buf += std::to_string(bufId) + ' ' + std::to_string(prio) + ' ';
  g_fake_log_buf += tag;
  g_fake_log_buf += ' ';
  g_fake_log_buf += msg;
  return 1;
}

extern "C" int __android_log_print(int prio, const char* tag, const char* fmt, ...) {
  g_fake_log_print += std::to_string(prio) + ' ';
  g_fake_log_print += tag;
  g_fake_log_print += ' ';

  va_list ap;
  va_start(ap, fmt);
  android::base::StringAppendV(&g_fake_log_print, fmt, ap);
  va_end(ap);

  g_fake_log_print += '\n';

  //std::cout<<tag<<":"<<g_fake_log_print.c_str()<<std::endl;

  return 1;
}

extern "C" log_id_t android_name_to_log_id(const char*) {
  return LOG_ID_SYSTEM;
}

extern "C" struct logger_list* android_logger_list_open(log_id_t, int, unsigned int, pid_t) {
  errno = EACCES;
  return nullptr;
}

extern "C" int android_logger_list_read(struct logger_list*, struct log_msg*) {
  return 0;
}

extern "C" EventTagMap* android_openEventTagMap(const char*) {
  return nullptr;
}

extern "C" int android_log_processBinaryLogBuffer(
    struct logger_entry*,
    AndroidLogEntry*, const EventTagMap*, char*, int) {
  return 0;
}

extern "C" void android_logger_list_free(struct logger_list*) {
}

extern "C" void __android_log_assert(const char* cond, const char* tag, const char* fmt,
                          ...){
    va_list ap;
    va_start(ap, fmt);
    __android_log_print(0, tag, fmt, ap);
    va_end(ap);
    abort();
}

extern "C" int __android_log_error_write(int tag, const char* subTag,
                                                int32_t uid, const char* data,
                                                uint32_t dataLen) {
    return 0;
}

extern "C"  int __android_log_is_loggable_len(int prio, const char* tag,
        size_t len,
        int default_prio) {
    return 0;
}

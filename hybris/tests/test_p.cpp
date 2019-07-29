/*
 * test_p.cpp
 *
 *  Created on: 2019 M07 29
 *      Author: jeremychen
 */
#include <stdio.h>
extern "C" void android_linker_init(int sdk_version, void* (*get_hooked_symbol)(const char*, const char*), int enable_linker_gdb_support);

int main() {
    android_linker_init(10, NULL, 0);
    return 0;
}

/*
 * ScopedTrace.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jeremychen
 */
#include "compat/hybris_compat.h"
#include "private/bionic_systrace.h"

ScopedTrace::ScopedTrace(const char* message __unused){}
ScopedTrace::~ScopedTrace(){}
void ScopedTrace::End(){}

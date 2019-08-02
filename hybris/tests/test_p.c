/*
 * test_p.cpp
 *
 *  Created on: 2019 M07 29
 *      Author: jeremychen
 */

#include <stdio.h>
#include <dlfcn.h>
#include <stddef.h>
#include <errno.h>
#include <EGL/egl.h>
#include <hybris/common/binding.h>

HYBRIS_LIBRARY_INITIALIZE(simple, "libsimple.so");
HYBRIS_IMPLEMENT_FUNCTION1(simple, double, mysqrt, double);

HYBRIS_LIBRARY_INITIALIZE(egl, "libEGL.so");
HYBRIS_IMPLEMENT_FUNCTION3(egl, EGLBoolean, eglInitialize, EGLDisplay, EGLint *, EGLint *);
HYBRIS_IMPLEMENT_FUNCTION5(egl, EGLBoolean, eglChooseConfig, EGLDisplay, const EGLint *, EGLConfig *, EGLint, EGLint *);
//HYBRIS_IMPLEMENT_FUNCTION1(egl, double, eglGetDisplay, double);

void *hello_handle;
void hybris_hello_initialize()
{
    hello_handle = android_dlopen("libhello.so", 0x00001); \
    printf("J:Here0 %p\n",hello_handle);
}

double mysqrt2(double n1) {
    static double (*f)(double) = (void *)0;
    if (!hello_handle)
    hybris_hello_initialize();
    if (*(&f) == (void *)0)
    {
        printf("J:Here1 %p\n", hello_handle);
        *(&f) = (void *) android_dlsym(hello_handle, "mysqrt2");
    }else{
        printf("J:Here2\n");
    }
    return f(n1);
}

static EGLDisplay  (*_eglGetDisplay)(EGLNativeDisplayType display_id) = NULL;

int main() {
    //mysqrt(7.0);
    printf("Hello Android Simple2\n");
    if(mysqrt != NULL) {
        printf("Not NULL\n");
        mysqrt(7.0);
    }else{
        printf("SHIT!!\n");
    }

    HYBRIS_DLSYSM(egl, &_eglGetDisplay, "eglGetDisplay");

    EGLDisplay display = _eglGetDisplay((void*)0);

    printf("OKOK\n\n");
    printf("Display = %p\n", display);

    EGLint majorVersion;
    EGLint minorVersion;
    EGLBoolean init = eglInitialize(display, &majorVersion, &minorVersion);
    printf("OKOK2 %d %d.%d\n\n", init, majorVersion, minorVersion);

    const EGLint attribs[] = {
            EGL_RED_SIZE,   8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE,  8,
            EGL_DEPTH_SIZE, 0,
            EGL_NONE
    };
    EGLint numConfigs;
    EGLConfig config;
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    printf("OKOK3 %p:%d\n\n", config, numConfigs);
    return 0;
}

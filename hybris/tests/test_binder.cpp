/*
 * testbinder.cpp
 *
 *  Created on: 2019 M08 5
 *      Author: jeremychen
 */
#include <iostream>
#include "linux/android/binder.h"

#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>
#include <binder/ProcessState.h>
#include <ui/DisplayInfo.h>
#include <utils/threads.h>
//#include <gui/ISurfaceComposer.h>
//#include <gui/Surface.h>
//#include <gui/SurfaceComposerClient.h>

using namespace std;
using namespace android;

class AThread : public Thread {
public:
    AThread()
        : Thread(false){}
private:
    virtual bool threadLoop() {
        cout<<"Hello AThread"<<endl;
        sleep(1);
        cout<<"Sleep 1: OK"<<endl;
        return false;
    }

    uint8_t* mExampleAudioData;
    int mExampleAudioLength;
};

class ISurfaceComposer: public IInterface {
public:
    DECLARE_META_INTERFACE(SurfaceComposer);
    virtual sp<IBinder> getBuiltInDisplay(int32_t id) = 0;
    /* returns information for each configuration of the given display
     * intended to be used to get information about built-in displays */
    virtual status_t getDisplayConfigs(const sp<IBinder>& display,
            Vector<DisplayInfo>* configs) = 0;
};

enum {
    eDisplayIdMain = 0,
    eDisplayIdHdmi = 1
};

enum {
    // Note: BOOT_FINISHED must remain this value, it is called from
    // Java by ActivityManagerService.
    BOOT_FINISHED = IBinder::FIRST_CALL_TRANSACTION,
    CREATE_CONNECTION,
    UNUSED, // formerly CREATE_GRAPHIC_BUFFER_ALLOC
    CREATE_DISPLAY_EVENT_CONNECTION,
    CREATE_DISPLAY,
    DESTROY_DISPLAY,
    GET_BUILT_IN_DISPLAY,
    SET_TRANSACTION_STATE,
    AUTHENTICATE_SURFACE,
    GET_SUPPORTED_FRAME_TIMESTAMPS,
    GET_DISPLAY_CONFIGS,
    GET_ACTIVE_CONFIG,
    SET_ACTIVE_CONFIG,
    CONNECT_DISPLAY,
    CAPTURE_SCREEN,
    CAPTURE_LAYERS,
    CLEAR_ANIMATION_FRAME_STATS,
    GET_ANIMATION_FRAME_STATS,
    SET_POWER_MODE,
    GET_DISPLAY_STATS,
    GET_HDR_CAPABILITIES,
    GET_DISPLAY_COLOR_MODES,
    GET_ACTIVE_COLOR_MODE,
    SET_ACTIVE_COLOR_MODE,
    ENABLE_VSYNC_INJECTIONS,
    INJECT_VSYNC,
    GET_LAYER_DEBUG_INFO,
    CREATE_SCOPED_CONNECTION,
    GET_DISPLAY_VIEWPORT,
    GET_DISPLAY_TYPE,
    GET_VIRTUAL_DISPLAY,
};

class BpSurfaceComposer : public BpInterface<ISurfaceComposer>
{
public:
    explicit BpSurfaceComposer(const sp<IBinder>& impl)
        : BpInterface<ISurfaceComposer>(impl)
    {
    }

    virtual ~BpSurfaceComposer() {}


    virtual sp<IBinder> getBuiltInDisplay(int32_t id) {
        Parcel data, reply;
        data.writeInterfaceToken(ISurfaceComposer::getInterfaceDescriptor());
        data.writeInt32(id);
        remote()->transact(GET_BUILT_IN_DISPLAY, data,
                &reply);
        return reply.readStrongBinder();
    }

    virtual status_t getDisplayConfigs(const sp<IBinder>& display,
                Vector<DisplayInfo>* configs)
    {
        cout<<"Called.........."<<__func__<<endl;
            Parcel data, reply;
            data.writeInterfaceToken(ISurfaceComposer::getInterfaceDescriptor());
            data.writeStrongBinder(display);
            remote()->transact(GET_DISPLAY_CONFIGS, data, &reply);
            status_t result = reply.readInt32();
            if (result == NO_ERROR) {
                size_t numConfigs = reply.readUint32();
                configs->clear();
                configs->resize(numConfigs);
                for (size_t c = 0; c < numConfigs; ++c) {
                    memcpy(&(configs->editItemAt(c)),
                            reply.readInplace(sizeof(DisplayInfo)),
                            sizeof(DisplayInfo));
                }
            }else{
                cout<<"Return with error "<<result<<endl;
            }
            return result;
        }
};

IMPLEMENT_META_INTERFACE(SurfaceComposer, "android.ui.ISurfaceComposer");

int main(int argc, char** argv) {

    sp<ProcessState> ps(ProcessState::self());
    ps->startThreadPool();


    sp<IServiceManager> sm = defaultServiceManager();
//    const String16 name("SurfaceFlinger");
//    printf("ServiceManager: %p\n", sm.get());
//    sp<IBinder> b = sm->getService(name);
//    printf("Service: %p\n", b.get());

//    Vector<String16> list = sm->listServices();
//        printf("ServiceList: %d\n", list.size());
    const String16 name("SurfaceFlinger");
    sp<ISurfaceComposer> mComposerService;
        while (getService(name, &mComposerService) != NO_ERROR) {
            usleep(250000);
        }
    printf("SurfaceFlinger = %p\n\n", mComposerService.get());

    sp<IBinder> display;
    Vector<DisplayInfo> configs;
    display = mComposerService->getBuiltInDisplay(eDisplayIdMain);
    if (display != NULL) {
        cout<<"Display ="<<display.get()<<endl;
    }
    mComposerService->getDisplayConfigs(display, &configs);

    cout<<display.get()<<":"<<configs.size()<<endl;

    if (configs.size() > 0) {
        cout<<configs[0].w<<":"<<configs[0].h<<endl;
    }
    return 0;
}

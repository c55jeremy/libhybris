#ifndef HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_0_IHWSERVICEMANAGER_H
#define HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_0_IHWSERVICEMANAGER_H

#include <hwbinder/IBinder.h>
#include <hwbinder/Parcel.h>
#include "../../../../../../android-p/autogen/android/hidl/base/1.0/BnHwBase.h"
#include "../../../../../../android-p/autogen/android/hidl/base/1.0/BpHwBase.h"
#include "../../../../../../android-p/autogen/android/hidl/base/1.0/hwtypes.h"
#include "../../../../../../android-p/autogen/android/hidl/manager/1.0/BnHwServiceNotification.h"
#include "../../../../../../android-p/autogen/android/hidl/manager/1.0/BpHwServiceNotification.h"
#include "../../../../../../android-p/autogen/android/hidl/manager/1.0/IServiceManager.h"
#include "../../../../../../android-p/system/libhidl/base/include/hidl/Status.h"

namespace android {
namespace hidl {
namespace manager {
namespace V1_0 {
::android::status_t readEmbeddedFromParcel(
        const ::android::hidl::manager::V1_0::IServiceManager::InstanceDebugInfo &obj,
        const ::android::hardware::Parcel &parcel,
        size_t parentHandle,
        size_t parentOffset);

::android::status_t writeEmbeddedToParcel(
        const ::android::hidl::manager::V1_0::IServiceManager::InstanceDebugInfo &obj,
        ::android::hardware::Parcel *parcel,
        size_t parentHandle,
        size_t parentOffset);

}  // namespace V1_0
}  // namespace manager
}  // namespace hidl
}  // namespace android

#endif  // HIDL_GENERATED_ANDROID_HIDL_MANAGER_V1_0_IHWSERVICEMANAGER_H

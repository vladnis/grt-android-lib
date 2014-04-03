LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := GRTprebuilt
LOCAL_SRC_FILES := GRTlib/libs/$(TARGET_ARCH_ABI)/libgrt.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/GRTlib/include

LOCAL_SHARED_LIBRARIES := gnustl_static
LOCAL_LDLIBS := -llog

include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := GRTwrapper
LOCAL_SRC_FILES := GRTwrapper.cpp

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := GRTprebuilt

include $(BUILD_SHARED_LIBRARY)
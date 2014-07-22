LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions

LOCAL_CPPFLAGS += -DCRYPTOPP_DISABLE_ASM -DCRYPTOPP_DISABLE_SSE2 -DCRYPTOPP_ENABLE_NAMESPACE_WEAK=1

LOCAL_MODULE := happymouse_shared

LOCAL_MODULE_FILENAME := libhappymouse

LOCAL_SRC_FILES := happymouse/main.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes


LOCAL_WHOLE_STATIC_LIBRARIES := cocos_happymouse_common


include $(BUILD_SHARED_LIBRARY)

$(call import-module,projects/HappyMouse)


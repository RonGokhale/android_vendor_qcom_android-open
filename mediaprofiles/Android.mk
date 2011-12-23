ifeq ($(call is-board-platform,msm7k),true)
LOCAL_PATH := $(call my-dir)

########################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := media_profiles_7627a.xml
LOCAL_MODULE := media_profiles.xml
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC

include $(BUILD_PREBUILT)
endif

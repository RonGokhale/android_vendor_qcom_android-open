ifeq ($(call is-board-platform-in-list,msm8960 msm8660 msm7627a),true)

LOCAL_PATH := $(my-dir)

########################
include $(CLEAR_VARS)

ifeq ($(call is-board-platform,msm7627a),true)
LOCAL_SRC_FILES := media_profiles_7627a.xml
else ifeq ($(call is-board-platform-in-list,msm8960 msm8660),true)
LOCAL_SRC_FILES := media_profiles.xml
endif

LOCAL_MODULE := media_profiles.xml

LOCAL_MODULE_TAGS := optional

# This will install the file in /system/etc
#
LOCAL_MODULE_CLASS := ETC

include $(BUILD_PREBUILT)
endif


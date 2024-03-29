LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := src/pv_omx_interface.cpp

LOCAL_MODULE := libqcomm_omx

LOCAL_MODULE_TAGS := optional

PV_TOP := external/opencore

PV_COPY_HEADERS_TO := libpv

PV_INCLUDES := \
    $(PV_TOP)/android \
    $(PV_TOP)/extern_libs_v2/khronos/openmax/include \
    $(PV_TOP)/engines/common/include \
    $(PV_TOP)/engines/player/config/core \
    $(PV_TOP)/engines/player/include \
    $(PV_TOP)/nodes/pvmediaoutputnode/include \
    $(PV_TOP)/nodes/pvdownloadmanagernode/config/opencore \
    $(PV_TOP)/pvmi/pvmf/include \
    $(PV_TOP)/fileformats/mp4/parser/config/opencore \
    $(PV_TOP)/oscl/oscl/config/android \
    $(PV_TOP)/oscl/oscl/config/shared \
    $(PV_TOP)/engines/author/include \
    $(PV_TOP)/android/drm/oma1/src \
    $(PV_TOP)/build_config/opencore_dynamic \
    $(TARGET_OUT_HEADERS)/$(PV_COPY_HEADERS_TO)

LOCAL_CFLAGS := $(PV_CFLAGS_MINUS_VISIBILITY)

LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
    $(PV_INCLUDES)

# Include Qualcomm codec
ifeq ($(TARGET_PRODUCT),dream)
LOCAL_SHARED_LIBRARIES := libOmxCore
endif

-include $(PV_TOP)/Android_platform_extras.mk

-include $(PV_TOP)/Android_system_extras.mk


include $(BUILD_SHARED_LIBRARY)


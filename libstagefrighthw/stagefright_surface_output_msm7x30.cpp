/*
 * Copyright (C) 2009 The Android Open Source Project
 * Copyright (c) 2010, Code Aurora Forum. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <media/stagefright/HardwareAPI.h>
#include "QComHardwareOverlayRenderer.h"
#include "QComHardwareRenderer.h"
#undef LOG_TAG
#define LOG_TAG "StagefrightSurfaceOutput7630"
#include <utils/Log.h>
//#define NDEBUG 0
#include "omx_drmplay_renderer.h"

using android::sp;
using android::ISurface;
using android::VideoRenderer;

VideoRenderer *createRenderer(
        const sp<ISurface> &surface,
        const char *componentName,
        OMX_COLOR_FORMATTYPE colorFormat,
        size_t displayWidth, size_t displayHeight,
        size_t decodedWidth, size_t decodedHeight,
        size_t rotation , size_t flags ) {
    using android::QComHardwareOverlayRenderer;
    using android::QComHardwareRenderer;


    static const int OMX_QCOM_COLOR_FormatYVU420SemiPlanar = 0x7FA30C00;
    static const int QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka = 0x7FA30C03;
    static const int QOMX_INTERLACE_FLAG = 0x49283654;
    static const int QOMX_3D_LEFT_RIGHT_VIDEO_FLAG = 0x23784238;
    static const int QOMX_3D_TOP_BOTTOM_VIDEO_FLAG = 0x4678239b;

    if (!strncmp(componentName, "OMX.qcom.video.decoder.", 23))
    {
        switch ((int)colorFormat)
        {
            case OMX_COLOR_FormatYUV420SemiPlanar:
            case OMX_QCOM_COLOR_FormatYVU420SemiPlanar:
            /*interlace variants*/
            case (OMX_QCOM_COLOR_FormatYVU420SemiPlanar ^ QOMX_INTERLACE_FLAG):
            case (QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka ^ QOMX_INTERLACE_FLAG):
            case (OMX_COLOR_FormatYUV420SemiPlanar ^ QOMX_INTERLACE_FLAG):
            /*3d variants*/
            case (QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka ^ QOMX_3D_TOP_BOTTOM_VIDEO_FLAG):
            case (QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka ^ QOMX_3D_LEFT_RIGHT_VIDEO_FLAG):
            {
                LOGV("StagefrightSurfaceOutput7x30::createRenderer");
                QComHardwareOverlayRenderer *videoRenderer =  new QComHardwareOverlayRenderer(
                    surface, colorFormat,
                    displayWidth, displayHeight,
                    decodedWidth, decodedHeight, rotation);
                bool initSuccess = videoRenderer->InitOverlayRenderer();
                if (!initSuccess)
                {
                    LOGE("Create Overlay Renderer failed");
                    delete videoRenderer;
                    break;
                }
                LOGV("Create Overlay Renderer successful");
                return static_cast<VideoRenderer *>(videoRenderer);
                break; //keep compiler quiet
            }
            case QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka:
            {
                LOGV("StagefrightSurfaceOutput7x30::createRenderer QComHardwareRenderer");
                return new QComHardwareRenderer(
                        surface, colorFormat,
                        displayWidth, displayHeight,
                        decodedWidth, decodedHeight, rotation);
                break; //keep compiler quiet
            }
            default:
                LOGE("ERR: Unsupported color format");
                //handle this outside the if statement
                break;
        }
    }  else if(!strncmp(componentName, "drm.play", 8)) {
              LOGV("StagefrightSurfaceOutput7x30::createRenderer for drm.play display *= %d,%d  decode = %d,%d", displayWidth, displayHeight, decodedWidth, decodedHeight);
              omx_drm_play_renderer::CreateRenderer(surface, decodedWidth, decodedHeight);
              return new omx_drm_dummy_renderer();
    }
    LOGE("error: StagefrightSurfaceOutput7x30::createRenderer returning NULL!");
    return NULL;
}

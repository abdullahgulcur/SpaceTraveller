#pragma once
#include <android/asset_manager.h>
#include <game-activity/native_app_glue/android_native_app_glue.h>
#include "Core.h"

namespace Engine{

    class AndroidAssetManager{
    private:
    public:

        AndroidAssetManager(){}
        ~AndroidAssetManager(){}

        template<typename T>
        void readBytesFromAsset(const char* filename, T& buffer) {

            AAsset* asset = AAssetManager_open(Core::getInstance()->app_->activity->assetManager, filename, AASSET_MODE_BUFFER);
            if (asset == nullptr) {
                std::cerr << "Failed to open asset file: " << filename << std::endl;
                return;
            }

            size_t fileLength = AAsset_getLength(asset);
            buffer.resize(fileLength);
            AAsset_read(asset, &buffer[0], fileLength);
            AAsset_close(asset);
        }
    };
}

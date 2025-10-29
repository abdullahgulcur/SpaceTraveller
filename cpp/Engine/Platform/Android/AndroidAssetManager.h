#pragma once
#include "AndroidApplication.h"

namespace Engine{

    class AndroidAssetManager{
    private:
    public:

        AndroidAssetManager(){}
        ~AndroidAssetManager(){}

        template<typename T>
        void readBytesFromAsset(const char* filename, T& buffer) {

            AAsset* asset = AAssetManager_open(AndroidApplication::getAssetManager(), filename, AASSET_MODE_BUFFER);
            if (asset == nullptr) {
                //std::cerr << "Failed to open asset file: " << filename << std::endl;
                return;
            }

            size_t fileLength = AAsset_getLength(asset);
            buffer.resize(fileLength);
            AAsset_read(asset, &buffer[0], fileLength);
            AAsset_close(asset);
        }
    };
}

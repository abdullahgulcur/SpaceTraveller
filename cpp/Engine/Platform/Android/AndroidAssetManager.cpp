/*
#include "pch.h"
#include "AndroidAssetManager.h"

namespace Engine{

    void AndroidAssetManager::readTextFileFromAssets(AAssetManager* assetManager, const char* filename, std::string& buffer) {
        AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
        if (asset == nullptr) {
            std::cerr << "Failed to open asset file: " << filename << std::endl;
            return;
        }

        size_t fileLength = AAsset_getLength(asset);
        buffer.resize(fileLength);
        AAsset_read(asset, &buffer[0], fileLength);
        AAsset_close(asset);
    }

    void AndroidAssetManager::readBytesFromAsset(AAssetManager* assetManager, const char* filename, std::vector<unsigned char>& buffer) {
        AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
        if (asset == nullptr) {
            std::cerr << "Failed to open asset file: " << filename << std::endl;
            return;
        }

        size_t fileLength = AAsset_getLength(asset);
        buffer.resize(fileLength);
        AAsset_read(asset, &buffer[0], fileLength);
        AAsset_close(asset);
    }

}*/

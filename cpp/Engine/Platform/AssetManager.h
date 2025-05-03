#pragma once

#if PLATFORM == ANDROID
#include "AndroidAssetManager.h"
#elif PLATFORM == WIN
#include "WindowsAssetManager.h"
#endif

namespace Engine{

    class AssetManager{
    private:
    public:

        AssetManager(){}
        ~AssetManager(){}

        template<typename T>
        void readBytesFromAsset(std::string filename, T& buffer) {
#if PLATFORM == ANDROID
            AndroidAssetManager androidAssetManager;
            androidAssetManager.readBytesFromAsset(filename.c_str(), buffer);
#elif PLATFORM == WIN
            WindowsAssetManager assetManager;
            std::string path = ASSETS_PATH + filename;
            assetManager.readBytesFromAsset(path.c_str(), buffer);
#endif
        }

        void getShaderMacros(std::string& macros){
#if PLATFORM == ANDROID
            macros += std::string("#version 320 es\n");
            macros += std::string("#define ANDROID") + std::string("\n");
#elif PLATFORM == WIN
            macros += std::string("#version 460 core\n");
            macros += std::string("#define WIN") + std::string("\n");
#endif
        }
    };
}
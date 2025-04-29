#pragma once

#ifdef PLATFORM "ANDROID"
#include "AndroidAssetManager.h"
#elif PLATFORM "WIN"
#endif

namespace Engine{

    class AssetManager{
    private:
    public:

        AssetManager(){}
        ~AssetManager(){}

        template<typename T>
        void readBytesFromAsset(const char* filename, T& buffer) {
#ifdef PLATFORM "ANDROID"
            AndroidAssetManager androidAssetManager;
            androidAssetManager.readBytesFromAsset(filename, buffer);
#elif PLATFORM "WIN"

#endif
        }

        void getShaderMacros(std::string& macros){
#ifdef PLATFORM "ANDROID"
            macros += std::string("#version 320 es\n");
#elif PLATFORM "WIN"

#endif
            macros += std::string("#define ") + std::string(PLATFORM) + std::string("\n");
        }
    };
}
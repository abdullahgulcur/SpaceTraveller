#pragma once
#include "GraphicsApi.h"

namespace Engine{

    namespace Texture{

        struct Texture2DConfig{
            const void* data = nullptr;
            unsigned int width = 0;
            unsigned int height = 0;
            unsigned int internalFormat = GL_RGB8;
            unsigned int format = GL_RGB;
            unsigned int type = GL_UNSIGNED_BYTE;
            unsigned int wrap_s = GL_REPEAT;
            unsigned int wrap_t  = GL_REPEAT;
            unsigned int minFilter = GL_LINEAR_MIPMAP_LINEAR;
            unsigned int magFilter = GL_LINEAR;
            unsigned int desiredChannels = 0;
        };

        struct TextureArray2DConfig {
            std::vector<void*> data;
            //const void* data = nullptr;
            unsigned int width = 0;
            unsigned int height = 0;
            unsigned int internalFormat = GL_RGB8;
            unsigned int format = GL_RGB;
            unsigned int type = GL_UNSIGNED_BYTE;
            unsigned int wrap_s = GL_REPEAT;
            unsigned int wrap_t = GL_REPEAT;
            unsigned int minFilter = GL_LINEAR_MIPMAP_LINEAR;
            unsigned int magFilter = GL_LINEAR;
            unsigned int desiredChannels = 0;
        };


        void createTexture2D(unsigned int& textureId, Texture2DConfig& config, std::string path);
        void createTexture2D(unsigned int& textureId, Texture2DConfig& config);
        void createTexture2D(unsigned int& textureId, std::string path);
        void createTextureArray2D(unsigned int& textureId, TextureArray2DConfig& config, std::vector<std::string> & pathList);
        void createTextureArray2D(unsigned int& textureId, std::vector<std::string>& pathList);
        void createTextureArray2D(unsigned int& textureId, TextureArray2DConfig& config);
        void texImage2D(unsigned int internalFormat, unsigned int format, unsigned int width, unsigned int height, unsigned int type, const void* data);
        void texImage2DArray(unsigned int internalFormat, unsigned int format, unsigned int width, unsigned int height, unsigned int layers, unsigned int type);
        void texParams2D(unsigned int wrap_s, unsigned int wrap_t, unsigned int minFilter, unsigned int magFilter);
        void texParams2DArray(unsigned int wrap_s, unsigned int wrap_t, unsigned int minFilter, unsigned int magFilter);
        void mipmapTex2D(unsigned int textureId);
        void mipmapTex2D();
        void mipmapTex2DArray();
        void bindTex2D(unsigned int textureId);
        void bindTexArray2D(unsigned int textureId);
        void generateTex(unsigned int& textureId);
        void unbindTex2D();
        void clearTex(unsigned int& textureId);
        //void setTexSlot2D(unsigned int slot, unsigned int textureId);
        void generateGalaxyFrameBufferTexture(unsigned int& galaxyTextureId, unsigned int dimension);

    }

//    class Texture2D {
//    private:
//    public:
//
//        unsigned int textureId;
//
//        Texture2D(){}
//        ~Texture2D(){}
//
//        Texture2D(std::vector<unsigned char>& buffer, unsigned int width, unsigned int height, unsigned int blockDimension);
//        Texture2D(const void* buffer, unsigned int width, unsigned int height, unsigned int channels);
//    };
}

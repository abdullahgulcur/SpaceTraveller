#pragma once

#include <GLES3/gl32.h>

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
        };

        void createTexture2D(unsigned int& textureId, Texture2DConfig& config);
        void texImage2D(unsigned int internalFormat, unsigned int format, unsigned int width, unsigned int height, unsigned int type, const void* data);
        void texParams2D(unsigned int wrap_s, unsigned int wrap_t, unsigned int minFilter, unsigned int magFilter);
        void mipmapTex2D(unsigned int textureId);
        void mipmapTex2D();
        void bindTex2D(unsigned int textureId);
        void generateTex(unsigned int& textureId);
        void unbindTex2D();
        void clearTex(unsigned int& textureId);
        void setTexSlot2D(unsigned int slot, unsigned int textureId);
        void generateGalaxyFrameBufferTexture(unsigned int& galaxyTextureId, unsigned int dimension);

    }

    class Texture2D {
    private:
    public:

        unsigned int textureId;

        Texture2D(){}
        ~Texture2D(){}

        Texture2D(std::vector<unsigned char>& buffer, unsigned int width, unsigned int height, unsigned int blockDimension);
        Texture2D(const void* buffer, unsigned int width, unsigned int height, unsigned int channels);
    };
}

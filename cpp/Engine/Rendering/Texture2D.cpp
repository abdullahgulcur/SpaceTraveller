#include "pch.h"
#include <GLES3/gl32.h>

#include "Texture2D.h"

namespace Engine{

    Texture2D::Texture2D(std::vector<unsigned char>& buffer, unsigned int width, unsigned int height, unsigned int blockDimension){

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        std::map<unsigned int, unsigned int> types;
        types[4] = GL_COMPRESSED_RGBA_ASTC_4x4;
        types[5] = GL_COMPRESSED_RGBA_ASTC_5x5;
        types[6] = GL_COMPRESSED_RGBA_ASTC_6x6;
        types[8] = GL_COMPRESSED_RGBA_ASTC_8x8;
        types[10] = GL_COMPRESSED_RGBA_ASTC_10x10;
        types[12] = GL_COMPRESSED_RGBA_ASTC_12x12;

        unsigned int internalFormat = types[blockDimension];

        glCompressedTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, buffer.size() - 16, &buffer[0] + 16);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture2D::Texture2D(const void* buffer, unsigned int width, unsigned int height, unsigned int channels){

        unsigned int formats[4] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
        unsigned int format = formats[channels - 1];

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }

}

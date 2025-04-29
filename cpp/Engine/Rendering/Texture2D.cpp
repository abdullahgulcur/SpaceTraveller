#include "pch.h"
#include "Texture2D.h"
#include "FrameBuffer.h"
#include "ShaderProgram.h"
#include "Core.h"
#include "TextureData.h"
#include "DrawCommand.h"
#include "AndroidAssetManager.h"
#include "stb_image.h"

namespace Engine{

    namespace Texture{

        void createTexture2D(unsigned int& textureId, Texture2DConfig& config, std::string path){

            std::vector<unsigned char> buffer;
            AndroidAssetManager androidAssetManager; // AssetManager !!!
            androidAssetManager.readBytesFromAsset(path.c_str(), buffer);

            int w, h, ch;
            void* data = stbi_load_from_memory(&buffer[0], (int)buffer.size(), &w, &h, &ch, config.desiredChannels);

            unsigned int internalFormats[4] = { GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 };
            unsigned int internalFormat = internalFormats[ch - 1];
            unsigned int formats[4] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
            unsigned int format = formats[ch - 1];

            config.width = w;
            config.height = h;
            config.internalFormat = internalFormat;
            config.format = format;
            config.data = data;

            createTexture2D(textureId, config);

            stbi_image_free(data);
        }

        void createTexture2D(unsigned int& textureId, Texture2DConfig& config){
            generateTex(textureId);
            bindTex2D(textureId);
            texImage2D(config.internalFormat, config.format, config.width, config.height, config.type, config.data);
            texParams2D(config.wrap_s, config.wrap_t, config.minFilter, config.magFilter);
            if(!config.data)
                return;
            if(config.minFilter == GL_LINEAR_MIPMAP_LINEAR || config.minFilter == GL_NEAREST_MIPMAP_LINEAR || config.minFilter == GL_NEAREST_MIPMAP_NEAREST || config.minFilter == GL_LINEAR_MIPMAP_NEAREST)
                mipmapTex2D();
        }

        void createTexture2D(unsigned int& textureId, std::string path){
            Texture2DConfig config;
            createTexture2D(textureId, config, path);
        }

        void texImage2D(unsigned int internalFormat, unsigned int format, unsigned int width, unsigned int height, unsigned int type, const void* data){
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
        }

        void texParams2D(unsigned int wrap_s, unsigned int wrap_t, unsigned int minFilter, unsigned int magFilter){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        }

        void mipmapTex2D(unsigned int textureId){
            bindTex2D(textureId);
            mipmapTex2D();
        }

        void mipmapTex2D(){
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void bindTex2D(unsigned int textureId){
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        void generateTex(unsigned int& textureId){
            glGenTextures(1, &textureId);
        }

        void unbindTex2D(){
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void clearTex(unsigned int& textureId){
            unbindTex2D();
            glDeleteTextures(1, &textureId);
        }

        void setTexSlot2D(unsigned int slot, unsigned int textureId){
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textureId);
        }

        // should be in asset manager, i think
        void generateGalaxyFrameBufferTexture(unsigned int& galaxyTextureId, unsigned int dimension){

            unsigned int noiseTextureId;
            createTexture2D(noiseTextureId, "texture/noise.jpg");

            Texture2DConfig galaxyTexConfig;
            galaxyTexConfig.width = dimension;
            galaxyTexConfig.height = dimension;
            galaxyTexConfig.internalFormat = GL_RGBA8;
            galaxyTexConfig.format = GL_RGBA;

            createTexture2D(galaxyTextureId, galaxyTexConfig);

            unsigned int fbo;
            FrameBuffer::generateFbo(fbo, galaxyTextureId, GL_COLOR_ATTACHMENT0);

            unsigned int galaxyShader;
            Shader::createShaderGalaxy(galaxyShader);

            glViewport(0, 0, dimension, dimension);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);

            Texture::setTexSlot2D(0, noiseTextureId);

            unsigned int vb;
            VertexBuffer::generateQuadVertexBuffer(vb);

            unsigned int vao;
            Vao::createQuadMeshVao(vao, vb);

            DrawCommand::drawQuad(vao);

            mipmapTex2D(galaxyTextureId);

            VertexBuffer::clear(vb);
            Vao::deleteVao(vao);
            Shader::deleteShaderProgram(galaxyShader);
            clearTex(noiseTextureId);
            FrameBuffer::deleteFbo(fbo);
        }

    }

//    Texture2D::Texture2D(std::vector<unsigned char>& buffer, unsigned int width, unsigned int height, unsigned int blockDimension){
//
//        glGenTextures(1, &textureId);
//        glBindTexture(GL_TEXTURE_2D, textureId);
//
//        std::map<unsigned int, unsigned int> types;
//        types[4] = GL_COMPRESSED_RGBA_ASTC_4x4;
//        types[5] = GL_COMPRESSED_RGBA_ASTC_5x5;
//        types[6] = GL_COMPRESSED_RGBA_ASTC_6x6;
//        types[8] = GL_COMPRESSED_RGBA_ASTC_8x8;
//        types[10] = GL_COMPRESSED_RGBA_ASTC_10x10;
//        types[12] = GL_COMPRESSED_RGBA_ASTC_12x12;
//
//        unsigned int internalFormat = types[blockDimension];
//
//        glCompressedTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, buffer.size() - 16, &buffer[0] + 16);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//
//    Texture2D::Texture2D(const void* buffer, unsigned int width, unsigned int height, unsigned int channels){
//
//        unsigned int formats[4] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
//        unsigned int format = formats[channels - 1];
//
//        glGenTextures(1, &textureId);
//        glBindTexture(GL_TEXTURE_2D, textureId);
//
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }

}

#include "pch.h"
#include "TextureData.h"
#include "AndroidAssetManager.h"
#include "stb_image.h"

namespace Engine{

    //---------------------- CompressedTextureData2D ----------------------

    CompressedTextureData2D::CompressedTextureData2D(std::string path){

        AndroidAssetManager androidAssetManager;
        androidAssetManager.readBytesFromAsset(path.c_str(), buffer);

        struct ASTCHeader {
            uint8_t magic[4];        // Magic number (always '13 ABAA')
            uint8_t blockDimX;       // Block width
            uint8_t blockDimY;       // Block height
            uint8_t blockDimZ;       // Block depth (usually 1 for 2D textures)
            uint8_t xSize[3];        // Texture width
            uint8_t ySize[3];        // Texture height
            uint8_t zSize[3];        // Texture depth (usually 1 for 2D textures)
        };

        ASTCHeader* header = reinterpret_cast<ASTCHeader*>(&buffer[0]);
        width = header->xSize[0] | (header->xSize[1] << 8) | (header->xSize[2] << 16);
        height = header->ySize[0] | (header->ySize[1] << 8) | (header->ySize[2] << 16);
        blockDimension = header->blockDimX;
    }

    //---------------------- TextureData2D ----------------------

    TextureData2D::TextureData2D(std::string path, unsigned int desiredChannels){

        std::vector<unsigned char> buffer;
        AndroidAssetManager androidAssetManager;
        androidAssetManager.readBytesFromAsset(path.c_str(), buffer);

        int w, h, ch;
        data = stbi_load_from_memory(&buffer[0], (int)buffer.size(), &w, &h, &ch, desiredChannels);
        width = w;
        height = h;
        channels = ch;
    }

    TextureData2D::~TextureData2D(){
        stbi_image_free((void*)data);
    }

}

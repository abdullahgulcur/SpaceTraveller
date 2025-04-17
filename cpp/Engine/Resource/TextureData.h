#pragma once

namespace Engine{

    class CompressedTextureData2D {
    private:
    public:

        std::vector<unsigned char> buffer;
        unsigned int width;
        unsigned int height;
        unsigned int blockDimension;

        CompressedTextureData2D(std::string path);
        ~CompressedTextureData2D(){}
    };

    class TextureData2D {
    private:
    public:

        const void* data = NULL;
        unsigned int width;
        unsigned int height;
        unsigned int channels;

        TextureData2D(std::string path, unsigned int desiredChannels);
        ~TextureData2D();
    };
}
#pragma once

namespace Engine{

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

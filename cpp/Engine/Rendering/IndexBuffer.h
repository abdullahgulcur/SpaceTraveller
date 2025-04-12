#pragma once

#include "glm.hpp"

namespace Engine {

    namespace IndexBuffer{

        struct IndexBuffer{
            unsigned int bufferId;
            unsigned int totalIndices;
            unsigned int indexElementType;
        };

        void generate(unsigned int& bufferId);
        void bind(unsigned int bufferId);
        void unbind();
        void clear(unsigned int& bufferId);
        unsigned int getIndexElementType(unsigned int maxIndex);
        void bufferData(unsigned int bufferId, unsigned int size, void* ptr);
        void bufferData(IndexBuffer& indexBuffer, unsigned char* indices, unsigned int totalIndices);
        void bufferData(IndexBuffer& indexBuffer, std::vector<unsigned int>& indices);
        //void draw(unsigned int totalIndices, unsigned int indexElementType);
        //void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount);
    }
}
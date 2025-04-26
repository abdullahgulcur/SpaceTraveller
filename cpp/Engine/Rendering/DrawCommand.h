#pragma once

namespace Engine{

    namespace DrawCommand {

        void draw(unsigned int totalIndices, unsigned int indexElementType);
        void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount);
        void drawInstanced(unsigned int vao, unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount);
        void drawArraysInstanced(unsigned int mode, unsigned int instanceCount);
        void drawBillboardsInstanced(unsigned int vao, unsigned int instanceCount);
        void drawQuadsInstanced(unsigned int vao, unsigned int instanceCount, unsigned int instanceBuffer, unsigned int stride, void* bufferPtr);
        void drawQuad(unsigned int vao);
    }
}

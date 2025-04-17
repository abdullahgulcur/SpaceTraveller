#pragma once

namespace Engine{

    namespace DrawCommand {

        void draw(unsigned int totalIndices, unsigned int indexElementType);
        void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount);
        void drawArraysInstanced(unsigned int mode, unsigned int instanceCount);
        void drawBillboardsInstanced(unsigned int vao, unsigned int instanceCount);
        void drawQuad(unsigned int vao);
    }
}

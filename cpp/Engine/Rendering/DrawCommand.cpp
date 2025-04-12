#include "DrawCommand.h"
#include <GLES3/gl32.h>

namespace Engine{

    namespace DrawCommand {

        void draw(unsigned int totalIndices, unsigned int indexElementType){
            glDrawElements(GL_TRIANGLES, totalIndices, indexElementType, (void*)0);
        }

        void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount){
            glDrawElementsInstanced(GL_TRIANGLES, totalIndices, indexElementType, (void*)0, instanceCount);
        }

        void drawBillboardsInstanced(unsigned int vao, unsigned int instanceCount){
            glBindVertexArray(vao);
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instanceCount);
        }

    }
}



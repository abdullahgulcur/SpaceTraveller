#include "DrawCommand.h"
#include "Vao.h"
#include "VertexBuffer.h"
#include "GraphicsApi.h"

namespace Engine{

    namespace DrawCommand {

        void draw(unsigned int totalIndices, unsigned int indexElementType){
            glDrawElements(GL_TRIANGLES, totalIndices, indexElementType, (void*)0);
        }

        void draw(unsigned int vao, unsigned int totalIndices, unsigned int indexElementType) {
            Vao::bind(vao);
            draw(totalIndices, indexElementType);
        }

        void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount){
            glDrawElementsInstanced(GL_TRIANGLES, totalIndices, indexElementType, (void*)0, instanceCount);
        }

        void drawInstanced(unsigned int vao, unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount){
            Vao::bind(vao);
            drawInstanced(totalIndices, indexElementType, instanceCount);
        }

        void drawQuad(unsigned int vao){
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        void drawQuadsInstanced(unsigned int vao, unsigned int instanceCount) {
            glBindVertexArray(vao);
            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instanceCount);
        }

        void drawQuadsInstanced(unsigned int vao, unsigned int instanceCount, unsigned int instanceBuffer, unsigned int stride, void* bufferPtr) {
            VertexBuffer::bufferSubData(instanceBuffer, 0, instanceCount * stride, bufferPtr);
            drawQuadsInstanced(vao, instanceCount);
        }

        void drawGrid(unsigned int vao, unsigned int vertexCount) {
            glBindVertexArray(vao);
            glDrawArrays(GL_LINES, 0, vertexCount);
        }

    }
}



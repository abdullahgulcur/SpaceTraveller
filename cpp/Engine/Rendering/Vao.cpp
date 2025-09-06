#include "pch.h"
#include "Vao.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsApi.h"
#include "ParticleSystem.h"

namespace Engine {

    namespace Vao {

        void generate(unsigned int& vao) {
            glGenVertexArrays(1, &vao);
        }

        void bind(unsigned int vao) {
            glBindVertexArray(vao);
        }

        void unbind() {
            glBindVertexArray(0);
        }

        void deleteVao(unsigned int& vao) {
            unbind();
            glDeleteVertexArrays(1, &vao);
        }

        void enableVertexAttributeArray(unsigned int index) {
            glEnableVertexAttribArray(index);
        }

        void vertexAttributePointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset) {
            enableVertexAttributeArray(index);
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
        }

        void vertexAttributePointerNormalized(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset) {
            enableVertexAttributeArray(index);
            glVertexAttribPointer(index, size, type, GL_TRUE, stride, (void*)offset);
        }

        void vertexAttributeIntegerPointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset) {
            enableVertexAttributeArray(index);
            glVertexAttribIPointer(index, size, type, stride, (void*)offset);
        }

        void vertexAttributePointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
            glVertexAttribDivisor(index, 1);
        }

        void vertexAttributePointerInstancedNormalized(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, type, GL_TRUE, stride, (void*)offset);
            glVertexAttribDivisor(index, 1);
        }

        void vertexAttributeIntegerPointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset) {
            glEnableVertexAttribArray(index);
            glVertexAttribIPointer(index, size, type, stride, (void*)offset);
            glVertexAttribDivisor(index, 1);
        }

        void createLitMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            IndexBuffer::bind(indexBufferId);
            vertexAttributePointer(0, 3, GL_FLOAT, 24, 0);
            vertexAttributePointer(1, 3, GL_FLOAT, 24, 12);
            unbind();
        }

        void createLitMeshTexturedVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            IndexBuffer::bind(indexBufferId);
            vertexAttributePointer(0, 3, GL_FLOAT, 32, 0);
            vertexAttributePointer(1, 3, GL_FLOAT, 32, 12);
            vertexAttributePointer(2, 2, GL_FLOAT, 32, 24);
            unbind();
        }

        void createBillboardMeshVao(unsigned int& vao, unsigned int vertexBufferId) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
            unbind();
        }

        void createQuadMeshVao(unsigned int& vao, unsigned int vertexBufferId) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
            unbind();
        }

        void createGridVao(unsigned int& vao, unsigned int vertexBufferId) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            vertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
            unbind();
        }


    }
}
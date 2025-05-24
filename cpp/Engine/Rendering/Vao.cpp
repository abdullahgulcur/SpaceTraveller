#include "pch.h"
#include "Vao.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsApi.h"
#include "ParticleSystem.h"

namespace Engine {

    namespace Vao{

        void generate(unsigned int& vao){
            glGenVertexArrays(1, &vao);
        }

        void bind(unsigned int vao) {
            glBindVertexArray(vao);
        }

        void unbind() {
            glBindVertexArray(0);
        }

        void deleteVao(unsigned int& vao){
            unbind();
            glDeleteVertexArrays(1, &vao);
        }

        void enableVertexAttributeArray(unsigned int index){
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

        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, bool textured) {
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            IndexBuffer::bind(indexBufferId);

            unsigned int stride = 24;
            if (textured) stride += 8;

            vertexAttributePointer(0, 3, GL_FLOAT, stride, 0);
            vertexAttributePointer(1, 3, GL_FLOAT, stride, 12);
            if (textured)
                vertexAttributePointer(2, 2, GL_FLOAT, stride, 24);

            unbind();
        }

        // for position data
        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, unsigned int instanceBufferId, bool textured){
            generate(vao);
            bind(vao);
            VertexBuffer::bind(vertexBufferId);
            IndexBuffer::bind(indexBufferId);

            unsigned int stride = 24;
            if(textured) stride += 8;

            unsigned int indexCounter = 0;

            vertexAttributePointer(0, 3, GL_FLOAT, stride, 0); indexCounter++;
            vertexAttributePointer(1, 3, GL_FLOAT, stride, 12); indexCounter++;

            if(textured){
                vertexAttributePointer(indexCounter, 2, GL_FLOAT, stride, 24); indexCounter++;
            }

            VertexBuffer::bind(instanceBufferId);

            vertexAttributePointerInstanced(indexCounter, 4, GL_FLOAT, 64, 0); indexCounter++;
            vertexAttributePointerInstanced(indexCounter, 4, GL_FLOAT, 64, 16); indexCounter++;
            vertexAttributePointerInstanced(indexCounter, 4, GL_FLOAT, 64, 32); indexCounter++;
            vertexAttributePointerInstanced(indexCounter, 4, GL_FLOAT, 64, 48); indexCounter++;

            unbind();
        }

        void createBillboardMeshVao(unsigned int& vao, unsigned int vertexBufferId){
            generate(vao);
            bind(vao);

            VertexBuffer::bind(vertexBufferId);

            vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);

            unbind();
        }

        void createParticleMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId) {

            generate(vao);
            bind(vao);

            VertexBuffer::bind(vertexBufferId);
            vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);
            
            VertexBuffer::bind(instanceBufferId);
            vertexAttributeIntegerPointerInstanced(1, 1, GL_UNSIGNED_SHORT, sizeof(ParticleSystem::ParticleGPUData), 0);
            vertexAttributeIntegerPointerInstanced(2, 3, GL_SHORT, sizeof(ParticleSystem::ParticleGPUData), 2);
            vertexAttributeIntegerPointerInstanced(3, 3, GL_BYTE, sizeof(ParticleSystem::ParticleGPUData), 8);
            vertexAttributePointerInstancedNormalized(4, 4, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUData), 11);
            vertexAttributeIntegerPointerInstanced(5, 1, GL_UNSIGNED_BYTE, sizeof(ParticleSystem::ParticleGPUData), 15);

            unbind();
        }

        void createGalaxyMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId){
            generate(vao);
            bind(vao);

            VertexBuffer::bind(vertexBufferId);

            vertexAttributePointer(0, 2, GL_FLOAT, 8, 0);

            VertexBuffer::bind(instanceBufferId);
            vertexAttributePointerInstanced(1, 4, GL_FLOAT, 80, 0);
            vertexAttributePointerInstanced(2, 4, GL_FLOAT, 80, 16);
            vertexAttributePointerInstanced(3, 4, GL_FLOAT, 80, 32);
            vertexAttributePointerInstanced(4, 4, GL_FLOAT, 80, 48);
            vertexAttributePointerInstanced(5, 4, GL_FLOAT, 80, 64);

            unbind();
        }

        void createQuadMeshVao(unsigned int& vao, unsigned int vertexBufferId){
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
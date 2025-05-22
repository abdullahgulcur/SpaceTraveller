#include "pch.h"
#include "VertexBuffer.h"
#include "GraphicsApi.h"

namespace Engine {

    namespace VertexBuffer{

        void generate(unsigned int& bufferId, unsigned int bufferSize, void* buffer){
            generate(bufferId);
            bufferData(bufferId, bufferSize, buffer);
        }

        void generate(unsigned int& bufferId){
            glGenBuffers(1, &bufferId);
        }

        void bind(unsigned int bufferId) {
            glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        }

        void bufferData(unsigned int bufferId, unsigned int bufferSize, void* buffer){
            bind(bufferId);
            glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);
        }

        void bufferSubData(unsigned int bufferId, unsigned int offset, unsigned int dataSize, void* data){
            bind(bufferId);
            glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, data);
        }

        void clear(unsigned int& bufferId) {
            unbind();
            glDeleteBuffers(1, &bufferId);
        }

        void unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void generateBillboardVertexBuffer(unsigned int& bufferId){

            float vertices[] = {
                    -0.5f, -0.5f,
                    0.5f, -0.5f,
                    -0.5f,  0.5f,
                    0.5f,  0.5f,
            };
            VertexBuffer::generate(bufferId,  sizeof(vertices), &vertices[0]);
        }

        void generateQuadVertexBuffer(unsigned int& bufferId){

            float vertices[] = {
                    -1.f, -1.f,
                    1.f, -1.f,
                    -1.f,  1.f,
                    1.f,  1.f,
            };
            VertexBuffer::generate(bufferId,  sizeof(vertices), &vertices[0]);
        }

        void generateGridVertexBuffer(unsigned int& bufferId, unsigned int& gridVertexCount) {

            // Parameters
            const int gridSize = 20; // grid lines from -gridSize to +gridSize
            std::vector<float> gridVertices;

            // Generate grid lines (XZ plane)
            for (int i = -gridSize; i <= gridSize; ++i) {
                // Vertical line (parallel to Z)
                gridVertices.push_back((float)i); gridVertices.push_back(0.0f); gridVertices.push_back((float)-gridSize);
                gridVertices.push_back((float)i); gridVertices.push_back(0.0f); gridVertices.push_back((float)gridSize);

                // Horizontal line (parallel to X)
                gridVertices.push_back((float)-gridSize); gridVertices.push_back(0.0f); gridVertices.push_back((float)i);
                gridVertices.push_back((float)gridSize);  gridVertices.push_back(0.0f); gridVertices.push_back((float)i);
            }

            VertexBuffer::generate(bufferId, gridVertices.size() * sizeof(float), &gridVertices[0]);

            gridVertexCount = gridVertices.size() / 3;
        }

    }
}
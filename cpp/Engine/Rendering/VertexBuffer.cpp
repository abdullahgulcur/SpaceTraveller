#include "VertexBuffer.h"

#include "pch.h"

#include <GLES3/gl32.h>

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
    }
}
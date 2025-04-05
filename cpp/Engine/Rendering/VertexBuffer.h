#pragma once

#include "glm.hpp"

namespace Engine {

    namespace VertexBuffer {

        struct VertexBuffer{
            unsigned int bufferId;
        };

        void generate(unsigned int& bufferId);
        void bind(unsigned int bufferId);
        void bufferData(unsigned int bufferId, unsigned int bufferSize, void* buffer);
        void clear(unsigned int& bufferId);
        void unbind();
    }
}
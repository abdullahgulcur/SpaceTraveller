#pragma once

#include "glm.hpp"

namespace Engine {

    class RenderBuffer {

    private:

    public:

        unsigned int id;

        RenderBuffer();
        ~RenderBuffer();
        void generateDepthRbo(glm::ivec2 size);
        void bind();
        void unbind();
        void generate();
        void setStorage(glm::ivec2 size);
        void deleteRbo();
    };

}

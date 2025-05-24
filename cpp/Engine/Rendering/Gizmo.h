#pragma once

#include "ShaderProgram.h"

namespace Engine {

    namespace Gizmo {

        struct Grid {
            unsigned int vao;
            Engine::Shader::ShaderGrid shaderProgram;
            unsigned int vertexCount;
        };


        void init(Grid& grid);
        void update(Grid& grid, glm::mat4& projectionView);
    }
}
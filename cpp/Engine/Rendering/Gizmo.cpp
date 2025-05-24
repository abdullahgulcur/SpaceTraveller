#include "pch.h"
#include "Gizmo.h"
#include "VertexBuffer.h"
#include "Vao.h"
#include "DrawCommand.h"

namespace Engine {

    namespace Gizmo {

        void init(Grid& grid) {

            unsigned int gridVertexBuffer;
            Engine::VertexBuffer::generateGridVertexBuffer(gridVertexBuffer, grid.vertexCount);
            Engine::Vao::createGridVao(grid.vao, gridVertexBuffer);
            Engine::Shader::createShaderGrid(grid.shaderProgram);
        }

        void update(Grid& grid, glm::mat4& projectionView) {

            Engine::Shader::updateUniforms(grid.shaderProgram, projectionView);
            Engine::DrawCommand::drawGrid(grid.vao, grid.vertexCount);
        }

    }
}
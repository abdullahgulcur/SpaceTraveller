#pragma once

#include "glm.hpp"

#include "Texture2D.h"

namespace Engine {

    namespace Shader{

        void createShaderProgram(unsigned int& shaderProgram, const char* vertexPath, const char* fragmentPath);
        void deleteShaderProgram(unsigned int& shaderProgram);

        void bind(unsigned int shaderProgramId);
        void unbind();

        void uniform(unsigned int location, float value);
        void uniform(unsigned int location, int value);
        void uniform(unsigned int location, unsigned int value);
        void uniform(unsigned int location, glm::vec2& value);
        void uniform(unsigned int location, glm::ivec2& value);
        void uniform(unsigned int location, glm::uvec2& value);
        void uniform(unsigned int location, glm::vec3& value);
        void uniform(unsigned int location, glm::mat4& value);
        
        void uniformTexture(unsigned int location, unsigned int slot, unsigned int textureId);
        void uniformTextureArray(unsigned int location, unsigned int slot, unsigned int textureId);
        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName);

    }

}
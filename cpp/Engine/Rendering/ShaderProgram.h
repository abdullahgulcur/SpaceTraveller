#pragma once

#include "glm.hpp"

namespace Engine {

    namespace Shader{

        struct ShaderProgramParticle {
            unsigned int programId;
            unsigned int locationView;
            unsigned int locationProjection;
        };

        void createShaderProgramParticle(ShaderProgramParticle& shaderProgramParticle);
        void updateUniformsShaderProgramParticle(ShaderProgramParticle& shaderProgramParticle, glm::mat4& projection, glm::mat4& view, unsigned int textureId);

        void createShaderProgram(unsigned int& shaderProgram, const char* vertexPath, const char* fragmentPath);
        void deleteShaderProgram(unsigned int& shaderProgram);
        void bind(unsigned int shaderProgramId);
        void unbind();

        void uniform(unsigned int location, glm::mat4& value);
        void uniform(unsigned int location, glm::vec3& value);
        void uniform(unsigned int location, glm::vec2& value);
        void uniform(unsigned int location, float value);
        void uniform(unsigned int location, int value);
        void uniform(unsigned int location, glm::ivec2& value);
        void uniform(unsigned int location, unsigned int value);
        void uniform(unsigned int location, glm::uvec2& value);
        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName);
    }

    class ShaderProgram {
    private:

    public:

        unsigned int programId;

        ShaderProgram(std::string vertexPath, std::string fragmentPath);
        ShaderProgram() {}
        ~ShaderProgram() {}

        void bind();
        void unbind();
        void clear();
        void uniform(std::string location, glm::mat4& value);
        void uniform(std::string location, glm::vec3& value);
        void uniform(std::string location, glm::vec2& value);
        void uniform(std::string location, float value);
        void uniform(std::string location, int value);
        void uniform(std::string location, glm::ivec2& value);
        void uniform(std::string location, unsigned int value);
        void uniform(std::string location, glm::uvec2& value);
    };
}
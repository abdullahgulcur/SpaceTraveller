#pragma once

#include "glm.hpp"

namespace Engine {

    class ShaderProgram {
    private:

    public:

        unsigned int programId;

        ShaderProgram(std::string& vertexPath, std::string& fragmentPath);
        ShaderProgram() {}
        ~ShaderProgram() {}

        void bind();
        void unbind();
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
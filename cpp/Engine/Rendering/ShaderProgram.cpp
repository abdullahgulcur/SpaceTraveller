#include "pch.h"
#include "ShaderProgram.h"
#include <GLES3/gl32.h>
#include "AndroidAssetManager.h"

namespace Engine {

    ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath){

        auto shaderCode = [](std::string& path, std::string& shaderCode) {
            AndroidAssetManager androidAssetManager;
            androidAssetManager.readBytesFromAsset(path.c_str(), shaderCode);
        };

        auto shaderCompile = [](std::string& path, std::string& shaderCode, unsigned int& shaderId) {
            printf("Compiling shader : %s\n", path.c_str());
            char const* sourcePointer = shaderCode.c_str();
            glShaderSource(shaderId, 1, &sourcePointer, NULL);
            glCompileShader(shaderId);

            GLint shaderCompiled = 0;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompiled);
            if (!shaderCompiled) {
                GLint infoLength = 0;
                glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength);

                if (infoLength) {
                    auto *infoLog = new GLchar[infoLength];
                    glGetShaderInfoLog(shaderId, infoLength, nullptr, infoLog);
                    //aout << "Failed to compile with:\n" << infoLog << std::endl;
                    delete[] infoLog;
                }
                glDeleteShader(shaderId);
                shaderId = 0;
            }
        };

        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderCode;
        std::string fragmentShaderCode;

        shaderCode(vertexPath, vertexShaderCode);
        shaderCode(fragmentPath, fragmentShaderCode);

        shaderCompile(vertexPath, vertexShaderCode, vertexShaderID);
        shaderCompile(fragmentPath, fragmentShaderCode, fragmentShaderID);

        programId = glCreateProgram();
        glAttachShader(programId, vertexShaderID);
        glAttachShader(programId, fragmentShaderID);
        glLinkProgram(programId);

        GLint linkStatus = GL_FALSE;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint logLength = 0;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

            // If we fail to link the shader program, log the result for debugging
            if (logLength) {
                GLchar *log = new GLchar[logLength];
                glGetProgramInfoLog(programId, logLength, nullptr, log);
                //aout << "Failed to link program with:\n" << log << std::endl;
                delete[] log;
            }
            glDeleteProgram(programId);
        }
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    void ShaderProgram::bind(){
        glUseProgram(programId);
    }

    void ShaderProgram::unbind(){
        glUseProgram(0);
    }

    void ShaderProgram::clear(){
        ShaderProgram::unbind();
        glDeleteShader(programId);
    }

    void ShaderProgram::uniform(std::string location, glm::mat4& value){
        glUniformMatrix4fv(glGetUniformLocation(programId, &location[0]), 1, GL_FALSE, &value[0][0]);
    }

    void ShaderProgram::uniform(std::string location, glm::vec3& value){
        glUniform3fv(glGetUniformLocation(programId, &location[0]), 1, &value[0]);
    }

    void ShaderProgram::uniform(std::string location, glm::vec2& value){
        glUniform2fv(glGetUniformLocation(programId, &location[0]), 1, &value[0]);
    }

    void ShaderProgram::uniform(std::string location, float value){
        glUniform1f(glGetUniformLocation(programId, &location[0]), value);
    }

    void ShaderProgram::uniform(std::string location, int value){
        glUniform1i(glGetUniformLocation(programId, &location[0]), value);
    }

    void ShaderProgram::uniform(std::string location, glm::ivec2& value){
        glUniform2iv(glGetUniformLocation(programId, &location[0]), 1, &value[0]);
    }

    void ShaderProgram::uniform(std::string location, unsigned int value){
        glUniform1ui(glGetUniformLocation(programId, &location[0]), value);
    }

    void ShaderProgram::uniform(std::string location, glm::uvec2& value){
        glUniform2uiv(glGetUniformLocation(programId, &location[0]), 1, &value[0]);
    }


}
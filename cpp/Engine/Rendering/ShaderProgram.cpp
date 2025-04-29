#include "pch.h"
#include "ShaderProgram.h"
#include "AssetManager.h"
#include "GraphicsApi.h"
#include "Texture2D.h"

namespace Engine {

    namespace Shader{

//        void createShaderParticlePST(SimpleShaderProgram& program){
//            createSimpleShaderProgram(program, "shader/particle_p_s.vert", "shader/particle.frag");
//        }

        void createShaderGalaxy(unsigned int& program){
            createShaderProgram(program, "shader/quad.vert", "shader/galaxy.frag");
            bind(program);
            //setTextureLocation(program, 0, "tex");
        }

        void createShaderParticlePS(SimpleShaderProgram& program){
            createSimpleShaderProgram(program, "shader/particle_p_s.vert", "shader/particle.frag");
        }

        void createShaderProgramParticle(SimpleShaderProgram& program){
            createSimpleShaderProgram(program, "shader/particle.vert", "shader/particle.frag");
        }

        void createShaderProgramParticleTextured(SimpleShaderProgram& program){
            createSimpleShaderProgram(program, "shader/particle.vert", "shader/particle_textured.frag");
            //setTextureLocation(program.programId, 0, "tex");
        }

        void createShaderProgramPhong(SimpleShaderProgram& program){
            createSimpleShaderProgram(program, "shader/phong.vert", "shader/phong.frag");
        }

        void createSimpleShaderProgram(SimpleShaderProgram& program, const char* vert, const char* frag){
            createShaderProgram(program.programId, vert, frag);
            bind(program.programId);
            getLocation(program.locationView, program.programId, "view");
            getLocation(program.locationProjection, program.programId, "projection");
        }

        void updateUniforms(SimpleShaderProgram& program, glm::mat4& projection, glm::mat4& view){
            bind(program.programId);
            uniform(program.locationProjection, projection);
            uniform(program.locationView, view);
        }

        void updateUniforms(SimpleShaderProgram& program, glm::mat4& projection, glm::mat4& view, unsigned int textureId){
            bind(program.programId);
            uniform(program.locationProjection, projection);
            uniform(program.locationView, view);
            Texture::setTexSlot2D(0, textureId);
        }

        void setTextureLocation(unsigned int& shaderProgramId, unsigned int index, const char* uniformName){
            unsigned int texLocation;
            getLocation(texLocation, shaderProgramId, uniformName);
            uniform(texLocation, index);
        }

        void createShaderProgram(unsigned int& shaderProgramId, const char* vertexPath, const char* fragmentPath){

            auto shaderCode = [](const char* path, std::string& shaderCode) {
                AssetManager assetManager;
                assetManager.readBytesFromAsset(path, shaderCode);
                std::string macros;
                assetManager.getShaderMacros(macros);
                shaderCode = macros + shaderCode;
            };

            auto shaderCompile = [](const char* path, std::string& shaderCode, unsigned int& shaderId) {
                printf("Compiling shader : %s\n", path);
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

            shaderProgramId = glCreateProgram();
            glAttachShader(shaderProgramId, vertexShaderID);
            glAttachShader(shaderProgramId, fragmentShaderID);
            glLinkProgram(shaderProgramId);

            GLint linkStatus = GL_FALSE;
            glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &linkStatus);
            if (linkStatus != GL_TRUE) {
                GLint logLength = 0;
                glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &logLength);

                // If we fail to link the shader program, log the result for debugging
                if (logLength) {
                    GLchar *log = new GLchar[logLength];
                    glGetProgramInfoLog(shaderProgramId, logLength, nullptr, log);
                    //aout << "Failed to link program with:\n" << log << std::endl;
                    delete[] log;
                }
                glDeleteProgram(shaderProgramId);
            }
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);
        }

        void deleteShaderProgram(unsigned int& shaderProgramId){
            unbind();
            glDeleteShader(shaderProgramId);
        }

        void bind(unsigned int shaderProgramId){
            glUseProgram(shaderProgramId);
        }

        void unbind(){
            glUseProgram(0);
        }

        void uniform(unsigned int location, glm::mat4& value){
            glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
        }

        void uniform(unsigned int location, glm::vec3& value){
            glUniform3fv(location, 1, &value[0]);
        }

        void uniform(unsigned int location, glm::vec2& value){
            glUniform2fv(location, 1, &value[0]);
        }

        void uniform(unsigned int location, float value){
            glUniform1f(location, value);
        }

        void uniform(unsigned int location, int value){
            glUniform1i(location, value);
        }

        void uniform(unsigned int location, glm::ivec2& value){
            glUniform2iv(location, 1, &value[0]);
        }

        void uniform(unsigned int location, unsigned int value){
            glUniform1ui(location, value);
        }

        void uniform(unsigned int location, glm::uvec2& value){
            glUniform2uiv(location, 1, &value[0]);
        }

        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName){
            location = glGetUniformLocation(shaderProgramId, uniformName);
        }


    }

}
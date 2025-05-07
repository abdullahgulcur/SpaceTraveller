#pragma once

#include "glm.hpp"

#include "Texture2D.h"

namespace Engine {

    namespace Shader{

        struct ShaderPV {
            unsigned int programId;
            unsigned int loc_ProjectionView;
        };

        struct ShaderPVM {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
        };

        struct ShaderPVC {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraPosition;
        };

        struct ShaderPVMC {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;
        };

        struct SimpleShaderProgram {
            unsigned int programId;
            unsigned int locationView;
            unsigned int locationProjection;
        };

        struct SimpleShaderProgram_ {
            unsigned int programId;
            unsigned int locationView;
            unsigned int locationProjection;
            unsigned int locationModel;
        };

        struct PlanetShader {
            unsigned int programId;
            unsigned int locationView;
            unsigned int locationProjection;
            unsigned int locationModel;
            unsigned int locationCameraPosition;
            unsigned int loc_WaterScale;
            unsigned int loc_WaterTreshold;
            unsigned int loc_WaterPower;
            unsigned int loc_WaterColor;
            unsigned int loc_WaterContinentalShelf;
            unsigned int loc_WaterDepth;

            unsigned int loc_Tex0;
            unsigned int loc_Tex1;

            /*unsigned int loc_;
            unsigned int loc_;
            unsigned int loc_;*/
            // tiling etc.
        };

//        struct ShaderParticlePS {
//            unsigned int programId;
//            unsigned int locationView;
//            unsigned int locationProjection;
//        };



        //void createShaderPhong(SimpleShaderProgram_& program);
        //void createShaderPhongTextured(SimpleShaderProgram_& program);
        //void createShaderPhongInstanced(SimpleShaderProgram_& program);
        //void createShaderPhongTexturedInstanced(SimpleShaderProgram_& program);


        void createShaderGalaxy(unsigned int& program);
        void createShaderParticlePS(SimpleShaderProgram& program);
        void createShaderProgramParticle(SimpleShaderProgram& program);
        void createShaderProgramParticleTextured(SimpleShaderProgram& program);
        void createSimpleShaderProgram(SimpleShaderProgram& program, const char* vert, const char* frag);
        void updateUniforms(SimpleShaderProgram& program, glm::mat4& projection, glm::mat4& view);
        void updateUniforms(SimpleShaderProgram& program, glm::mat4& projection, glm::mat4& view, unsigned int textureId);
        void createShaderProgramPhong(SimpleShaderProgram& program);
        //void createShaderProgram_(SimpleShaderProgram_& program);
        void createShaderPlanet(PlanetShader& shader);
        void createShaderPlanet(PlanetShader& shader, const char* vert, const char* frag);

        void setTextureLocation(unsigned int& shaderProgramId, unsigned int index, const char* uniformName);

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
        void uniform(unsigned int location, unsigned int slot, unsigned int textureId);
        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName);


        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model) {
            bind(program.programId);
            uniform(program.locationProjection, projection);
            uniform(program.locationView, view);
            uniform(program.locationModel, model);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, glm::vec3& cameraPosition) {
            updateUniforms(program, projection, view, model);
            uniform(program.locationCameraPosition, cameraPosition);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, unsigned int tex0) {
            updateUniforms(program, projection, view, model);
            Texture::setTexSlot2D(0, tex0);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, glm::vec3& cameraPosition, unsigned int tex0) {
            updateUniforms(program, projection, view, model, cameraPosition);
            Texture::setTexSlot2D(0, tex0);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, glm::vec3& cameraPosition,
                            glm::vec3& waterColor, float waterScale, float waterTreshold, float waterPower, float waterContinentalShelf, float waterDepth,
                            unsigned int tex0, unsigned int tex1) {
            updateUniforms(program, projection, view, model, cameraPosition);
            uniform(program.loc_WaterScale, waterScale);
            uniform(program.loc_WaterTreshold, waterTreshold);
            uniform(program.loc_WaterPower, waterPower);
            uniform(program.loc_WaterColor, waterColor);
            uniform(program.loc_WaterContinentalShelf, waterContinentalShelf);
            uniform(program.loc_WaterDepth, waterDepth);
            uniform(program.loc_Tex0, 0, tex0);
            uniform(program.loc_Tex1, 1, tex1);

            //uniform(1, tex1);
        }
    }

//
//    class ShaderProgram {
//    private:
//
//    public:
//
//        unsigned int programId;
//
//        ShaderProgram(std::string vertexPath, std::string fragmentPath);
//        ShaderProgram() {}
//        ~ShaderProgram() {}
//
//        void bind();
//        void unbind();
//        void clear();
//        void uniform(std::string location, glm::mat4& value);
//        void uniform(std::string location, glm::vec3& value);
//        void uniform(std::string location, glm::vec2& value);
//        void uniform(std::string location, float value);
//        void uniform(std::string location, int value);
//        void uniform(std::string location, glm::ivec2& value);
//        void uniform(std::string location, unsigned int value);
//        void uniform(std::string location, glm::uvec2& value);
//    };
}
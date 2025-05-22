#pragma once

#include "glm.hpp"

#include "Texture2D.h"

namespace Engine {

    namespace Shader{

        struct ShaderGrid {
            unsigned int programId;
            unsigned int loc_ProjectionView;
        };

        struct ShaderPhong {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;
        };

        struct ShaderPhongTextured {
            unsigned int programId;
            unsigned int loc_View;
            unsigned int loc_Projection;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;
            unsigned int loc_Tex;
        };

        struct ShaderParticle {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
        };

        struct ShaderParticleTextured {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
            unsigned int loc_Tex;
        };

        struct PlanetShader {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;
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

        void createShaderGrid(ShaderGrid& program);
        void createShaderParticle(ShaderParticle& program);
        void createShaderParticle(ShaderParticleTextured& program);
        void createShaderGalaxy(unsigned int& program);
        void createShaderPhong(ShaderPhongTextured& program);
        void createShaderPhong(ShaderPhong& program);
        void createShaderPlanet(PlanetShader& shader);
        void createShaderPlanet(PlanetShader& shader, const char* vert, const char* frag);

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
        void setTextureLocation(unsigned int& shaderProgramId, unsigned int index, const char* uniformName);
        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName);

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView) {
            bind(program.programId);
            uniform(program.loc_ProjectionView, projectionView);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView, glm::vec3& cameraRight, glm::vec3& cameraUp) {
            bind(program.programId);
            uniform(program.loc_ProjectionView, projectionView);
            uniform(program.loc_CameraRight, cameraRight);
            uniform(program.loc_CameraUp, cameraUp);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView, glm::mat4& model) {
            bind(program.programId);
            uniform(program.loc_ProjectionView, projectionView);
            uniform(program.loc_Model, model);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView, glm::mat4& model, glm::vec3& cameraPosition) {
            updateUniforms(program, projectionView, model);
            uniform(program.loc_CameraPosition, cameraPosition);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView, glm::mat4& model, glm::vec3& cameraPosition, unsigned int tex) {
            updateUniforms(program, projectionView, model, cameraPosition);
            uniform(program.loc_Tex, 0, tex);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projectionView, glm::mat4& model, glm::vec3& cameraPosition,
                            glm::vec3& waterColor, float waterScale, float waterTreshold, float waterPower, float waterContinentalShelf, float waterDepth,
                            unsigned int tex0, unsigned int tex1) {
            updateUniforms(program, projectionView, model, cameraPosition);
            uniform(program.loc_WaterScale, waterScale);
            uniform(program.loc_WaterTreshold, waterTreshold);
            uniform(program.loc_WaterPower, waterPower);
            uniform(program.loc_WaterColor, waterColor);
            uniform(program.loc_WaterContinentalShelf, waterContinentalShelf);
            uniform(program.loc_WaterDepth, waterDepth);
            uniform(program.loc_Tex0, 0, tex0);
            uniform(program.loc_Tex1, 1, tex1);
        }

        template <typename T>
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, glm::vec3& cameraPosition, unsigned int tex) {
            updateUniforms(program, projection, view, model, cameraPosition);
            uniform(program.loc_Tex, 0, tex);
        }
    }

}
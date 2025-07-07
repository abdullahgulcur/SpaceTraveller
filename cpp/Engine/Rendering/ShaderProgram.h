#pragma once

#include "glm.hpp"

#include "Texture2D.h"

namespace Engine {

    namespace Shader{

        struct PlanetShaderData {
            unsigned int programId;
            glm::mat4 projectionView;
            glm::mat4 model;
            glm::vec3 cameraPosition;
            glm::vec3 waterColor;
            glm::vec3 continentalShelfColor;
            glm::vec3 lightDirection;
            glm::vec3 landColor0;
            glm::vec3 landColor1;
            float landColorOverlay;
            float landColorPower;
            float waterScale;
            float waterTreshold;
            float waterPower;
            float waterContinentalShelf;
            float waterDepth;
            float surfaceTopologyScale;
            float landColorBlendScale;

            float macroScale;
            float cloudScale;
            float cloudPower;
            float cloudOverlay;
            float cloudOpacity;
            glm::vec3 cloudColor;
            float fresnelPowerClouds;
            float fresnelScaleClouds;
            float fresnelBiasClouds;
            float fresnelPowerAtmosphere;
            float fresnelScaleAtmosphere;
            float fresnelBiasAtmosphere;

            float noiseOctaveTexIndex0;
            float noiseOctaveTexIndex1;
            float noiseOctaveTexIndex2;

            unsigned int tex0;
            unsigned int tex1;
            unsigned int texArray;
        };

        struct ShaderGrid {
            unsigned int programId;
            unsigned int loc_ProjectionView;
        };

        //struct ShaderPhong {
        //    unsigned int programId;
        //    unsigned int loc_ProjectionView;
        //    unsigned int loc_Model;
        //    unsigned int loc_CameraPosition;
        //};

        //struct ShaderPhongTextured {
        //    unsigned int programId;
        //    unsigned int loc_View;
        //    unsigned int loc_Projection;
        //    unsigned int loc_Model;
        //    unsigned int loc_CameraPosition;
        //    unsigned int loc_Tex;
        //};

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

        struct ShaderParticleSolarSystem {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
            unsigned int loc_Tex;
            unsigned int loc_AspectRatio;
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

            unsigned int loc_LandColor0;
            unsigned int loc_LandColor1;
            unsigned int loc_LandColorOverlay;
            unsigned int loc_LandColorPower;

            unsigned int loc_ContinentalShelfColor;
            unsigned int loc_WaterContinentalShelf;
            unsigned int loc_WaterDepth;
            unsigned int loc_LightDirection;

            unsigned int loc_SurfaceTopologyScale;
            unsigned int loc_LandColorBlendScale;

            unsigned int loc_Tex0;
            unsigned int loc_Tex1;
            unsigned int loc_TexArray;


            unsigned int loc_MacroScale;
            unsigned int loc_CloudScale;
            unsigned int loc_CloudPower;
            unsigned int loc_CloudOverlay;
            unsigned int loc_CloudOpacity;
            unsigned int loc_CloudColor;
            unsigned int loc_FresnelPowerClouds;
            unsigned int loc_FresnelScaleClouds;
            unsigned int loc_FresnelBiasClouds;
            unsigned int loc_FresnelPowerAtmosphere;
            unsigned int loc_FresnelScaleAtmosphere;
            unsigned int loc_FresnelBiasAtmosphere;

            unsigned int loc_NoiseOctaveTexIndex0;
            unsigned int loc_NoiseOctaveTexIndex1;
            unsigned int loc_NoiseOctaveTexIndex2;

        };

        struct ShaderSun {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
        };

        struct ShaderTerrain {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraPosition;
            unsigned int loc_BlockSize;
        };

        
        void createShaderGrid(ShaderGrid& program);
        void createShaderParticle(ShaderParticle& program);
        void createShaderParticle(ShaderParticleTextured& program);
        void createShaderParticleSolarSystem(ShaderParticleSolarSystem& shader);
        void createShaderTerrain(ShaderTerrain& shader);
        void createShaderGalaxy(unsigned int& program);
        //void createShaderPhong(ShaderPhongTextured& program);
        //void createShaderPhong(ShaderPhong& program);
        void createShaderPlanet(PlanetShader& shader);
        void createShaderSun(ShaderSun& shader);
        void createShaderPlanet(PlanetShader& shader, const char* vert, const char* frag);

        void updateUniforms(PlanetShader& shader, PlanetShaderData& planetShaderData);

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
        void uniformTextureArray(unsigned int location, unsigned int slot, unsigned int textureId);
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
        void updateUniformsParticleFixedSize(T& program, glm::mat4& projectionView, glm::vec3& cameraRight, glm::vec3& cameraUp, float aspectRatio) {
            bind(program.programId);
            uniform(program.loc_ProjectionView, projectionView);
            uniform(program.loc_CameraRight, cameraRight);
            uniform(program.loc_CameraUp, cameraUp);
            uniform(program.loc_AspectRatio, aspectRatio);
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
        void updateUniforms(T& program, glm::mat4& projection, glm::mat4& view, glm::mat4& model, glm::vec3& cameraPosition, unsigned int tex) {
            updateUniforms(program, projection, view, model, cameraPosition);
            uniform(program.loc_Tex, 0, tex);
        }

        void updateUniforms(ShaderTerrain& program, glm::mat4& projectionView, glm::vec3& cameraPosition, unsigned int blockSize);
    }

}
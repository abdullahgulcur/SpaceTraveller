#pragma once

#include "glm.hpp"

#include "Universe.h"
#include "Camera.h"

#include "Texture2D.h"

namespace Game {

    namespace Shader {

        struct ShaderPlanet {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;
            unsigned int loc_WaterScale;
            unsigned int loc_AmountWater;
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

            unsigned int loc_SpecularStrength;
            unsigned int loc_SpecularPower;

            unsigned int loc_NoiseOctaveTexIndex0;
            unsigned int loc_NoiseOctaveTexIndex1;

        };

        struct ShaderDataPlanet {
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
            float amountWater;
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
            float specularStrength;
            float specularPower;

            float noiseOctaveTexIndex0;
            float noiseOctaveTexIndex1;
            float noiseOctaveTexIndex2;

            //unsigned int tex0;
            //unsigned int tex1;
            unsigned int texArray;

            ShaderDataPlanet(){}

            ShaderDataPlanet(Planet& planet, Engine::Camera::Camera& camera, glm::mat4& model, glm::vec3& lightDirection, unsigned int& noiseTextureArrayId) {

                cameraPosition = camera.position;
                projectionView = camera.projectionView;
                this->model = model;
                waterColor = planet.waterColor;
                amountWater = planet.amountWater;
                continentalShelfColor = planet.continentalShelfColor;
                waterContinentalShelf = planet.continentalShelf;
                this->lightDirection = lightDirection;
                landColor0 = planet.landColor0;
                landColor1 = planet.landColor1;
                landColorOverlay = planet.landColorOverlay;
                landColorPower = planet.landColorPower;
                surfaceTopologyScale = planet.surfaceTopologyScale;
                landColorBlendScale = planet.landColorBlendScale;
                texArray = noiseTextureArrayId;

                macroScale = planet.macroScale;
                cloudScale = planet.cloudScale;
                cloudPower = planet.cloudPower;
                cloudOverlay = planet.cloudOverlay;
                cloudOpacity = planet.cloudOpacity;
                cloudColor = planet.cloudColor;
                fresnelPowerClouds = planet.fresnelPowerClouds;
                fresnelScaleClouds = planet.fresnelScaleClouds;
                fresnelBiasClouds = planet.fresnelBiasClouds;
                fresnelPowerAtmosphere = planet.fresnelPowerAtmosphere;
                fresnelScaleAtmosphere = planet.fresnelScaleAtmosphere;
                fresnelBiasAtmosphere = planet.fresnelBiasAtmosphere;

                noiseOctaveTexIndex0 = float(planet.noiseOctaveTexIndex0);
                noiseOctaveTexIndex1 = float(planet.noiseOctaveTexIndex1);
                noiseOctaveTexIndex2 = float(planet.noiseOctaveTexIndex2);
                specularStrength = planet.specularStrength;
                specularPower = planet.specularPower;
            }
        };

        struct ShaderSun {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_Model;
            unsigned int loc_CameraPosition;

            unsigned int loc_Color0;
            unsigned int loc_Color1;
            unsigned int loc_Color2;
            unsigned int loc_Color3;
            unsigned int loc_ColorOverlay0;
            unsigned int loc_ColorOverlay1;
            unsigned int loc_ColorPower0;
            unsigned int loc_ColorPower1;
            unsigned int loc_NoiseScale;
            unsigned int loc_NoiseTexIndex;

            unsigned int loc_TexArray;

            unsigned int loc_FresnelPower;
            unsigned int loc_FresnelScale;
            unsigned int loc_FresnelBias;
        };

        struct ShaderDataSun {
            glm::mat4 projectionView;
            glm::mat4 model;
            glm::vec3 cameraPosition;

            glm::vec3 color0;
            glm::vec3 color1;
            glm::vec3 color2;
            glm::vec3 color3;
            float colorOverlay0;
            float colorOverlay1;
            float colorPower0;
            float colorPower1;
            float noiseScale;
            float noiseTexIndex;
            unsigned int texArray;
            float fresnelPower;
            float fresnelScale;
            float fresnelBias;
        };

        //struct ShaderGrid {
        //    unsigned int programId;
        //    unsigned int loc_ProjectionView;
        //};

        struct ShaderParticle {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
        };

        struct ShaderDataParticle {
            glm::mat4 projectionView;
            glm::vec3 cameraRight;
            glm::vec3 cameraUp;
        };

        struct ShaderParticleTextured {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
            unsigned int loc_Tex;
        };

        struct ShaderDataParticleTextured {
            glm::mat4 projectionView;
            glm::vec3 cameraRight;
            glm::vec3 cameraUp;
            unsigned int textureId;
        };

        struct ShaderParticleSolarSystem {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraRight;
            unsigned int loc_CameraUp;
            unsigned int loc_CameraPosition;
            unsigned int loc_Tex;
            unsigned int loc_AspectRatio;
        };

        struct ShaderDataParticleSolarSystem {
            glm::mat4 projectionView;
            glm::vec3 cameraRight;
            glm::vec3 cameraUp;
            glm::vec3 cameraPosition;
            float aspectRatio;
            unsigned int textureId; // const
        };

        struct ShaderTerrain {
            unsigned int programId;
            unsigned int loc_ProjectionView;
            unsigned int loc_CameraPosition;
            unsigned int loc_BlockSize;
        };

        struct ShaderDataTerrain {
            glm::mat4 projectionView;
            glm::vec3 cameraPosition;
            unsigned int blockSize;
        };

        struct ShaderFXAA {
            unsigned int programId;
            unsigned int loc_Tex;
            unsigned int loc_ScreenSize;
        };

        struct ShaderDataFXAA {
            glm::ivec2 screenSize;
            unsigned int textureId;
        };

        struct ShaderTextureGeneratorSun {
            unsigned int programId;
            unsigned int loc_Tex;
        };

        struct ShaderDataTextureGeneratorSun {
            unsigned int textureId;
        };

        //void createShader(ShaderGrid& program);
        void createShader(ShaderParticle& program);
        void createShader(ShaderParticleTextured& program);
        void createShader(ShaderParticleSolarSystem& shader);
        void createShader(ShaderTerrain& shader);
        void createShader(ShaderFXAA& shader);
        void createShader(ShaderTextureGeneratorSun& program);
        void createShader(ShaderPlanet& shader);
        void createShader(ShaderSun& shader);
        void createShader(ShaderPlanet& shader);

        void updateUniforms(ShaderPlanet& shader, ShaderDataPlanet& planetShaderData);
        void updateUniforms(ShaderSun& shader, ShaderDataSun& shaderDataSun);
        void updateUniforms(ShaderParticleSolarSystem& program, ShaderDataParticleSolarSystem& shaderData);

        void updateUniforms(ShaderTerrain& program, ShaderDataTerrain& shaderData);
        void updateUniforms(ShaderFXAA& program, ShaderDataFXAA& shaderData);
        //void updateUniforms(ShaderGrid& shaderProgram, glm::mat4& projectionView);

    }

}
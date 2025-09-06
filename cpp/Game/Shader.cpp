#include "pch.h"
#include "Shader.h"
#include "ShaderProgram.h"

namespace Game {

    namespace Shader {

        void createShader(ShaderTextureGeneratorSun& program) {

            std::string vertShader = "shader/quad.vert";
            std::string fragShader = "shader/tex_gen_sun.frag";

            Engine::Shader::createShaderProgram(program.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(program.programId);
            Engine::Shader::getLocation(program.loc_Tex, program.programId, "tex");
        }

        /*void createShader(ShaderGrid& program) {
            Engine::Shader::createShaderProgram(program.programId, "shader/grid.vert", "shader/grid.frag");
            Engine::Shader::bind(program.programId);
            Engine::Shader::getLocation(program.loc_ProjectionView, program.programId, "projectionView");
        }*/

        void createShader(ShaderParticle& program) {

            std::string vertShader = "shader/particle/vert/particle.vert";
            std::string fragShader = "shader/particle/frag/particle_base.frag";

            Engine::Shader::createShaderProgram(program.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(program.programId);
            Engine::Shader::getLocation(program.loc_ProjectionView, program.programId, "projectionView");
            Engine::Shader::getLocation(program.loc_CameraRight, program.programId, "cameraRight");
            Engine::Shader::getLocation(program.loc_CameraUp, program.programId, "cameraUp");
        }

        void createShader(ShaderParticleTextured& program) {

            std::string vertShader = "shader/particle/vert/particle.vert";
            std::string fragShader = "shader/particle/frag/particle_texture.frag";

            Engine::Shader::createShaderProgram(program.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(program.programId);
            Engine::Shader::getLocation(program.loc_ProjectionView, program.programId, "projectionView");
            Engine::Shader::getLocation(program.loc_CameraRight, program.programId, "cameraRight");
            Engine::Shader::getLocation(program.loc_CameraUp, program.programId, "cameraUp");
            Engine::Shader::getLocation(program.loc_Tex, program.programId, "tex");
        }

        void createShader(ShaderParticleSolarSystem& shader) {

            std::string vertShader = "shader/particle/vert/particle_solar_system.vert";
            std::string fragShader = "shader/particle/frag/particle_texture.frag";
            //std::string fragShader = "shader/particle/frag/particle_base.frag";

            Engine::Shader::createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(shader.programId);
            Engine::Shader::getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            Engine::Shader::getLocation(shader.loc_CameraRight, shader.programId, "cameraRight");
            Engine::Shader::getLocation(shader.loc_CameraUp, shader.programId, "cameraUp");
            Engine::Shader::getLocation(shader.loc_AspectRatio, shader.programId, "aspectRatio");
            Engine::Shader::getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");
            Engine::Shader::getLocation(shader.loc_Tex, shader.programId, "tex");
        }

        void createShader(ShaderTerrain& shader) {

            std::string vertShader = "shader/terrain/terrain.vert";
            std::string fragShader = "shader/terrain/terrain.frag";

            Engine::Shader::createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(shader.programId);
            Engine::Shader::getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            Engine::Shader::getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");
            Engine::Shader::getLocation(shader.loc_BlockSize, shader.programId, "blockSize");
        }

        void createShader(ShaderFXAA& shader) {

            std::string vertShader = "shader/quad.vert";
            std::string fragShader = "shader/postprocess/fxaa.frag";

            Engine::Shader::createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(shader.programId);
            Engine::Shader::getLocation(shader.loc_Tex, shader.programId, "tex");
            Engine::Shader::getLocation(shader.loc_ScreenSize, shader.programId, "screenSize");
        }

        void createShader(ShaderSun& shader) {

            Engine::Shader::createShaderProgram(shader.programId, "shader/lit_textured.vert", "shader/sun.frag");
            Engine::Shader::bind(shader.programId);

            Engine::Shader::getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            Engine::Shader::getLocation(shader.loc_Model, shader.programId, "model");
            Engine::Shader::getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");

            Engine::Shader::getLocation(shader.loc_Color0, shader.programId, "color0");
            Engine::Shader::getLocation(shader.loc_Color1, shader.programId, "color1");
            Engine::Shader::getLocation(shader.loc_Color2, shader.programId, "color2");
            Engine::Shader::getLocation(shader.loc_Color3, shader.programId, "color3");
            Engine::Shader::getLocation(shader.loc_ColorOverlay0, shader.programId, "colorOverlay0");
            Engine::Shader::getLocation(shader.loc_ColorOverlay1, shader.programId, "colorOverlay1");
            Engine::Shader::getLocation(shader.loc_ColorPower0, shader.programId, "colorPower0");
            Engine::Shader::getLocation(shader.loc_ColorPower1, shader.programId, "colorPower1");
            Engine::Shader::getLocation(shader.loc_NoiseScale, shader.programId, "noiseScale");
            Engine::Shader::getLocation(shader.loc_NoiseTexIndex, shader.programId, "noiseTexIndex");
            Engine::Shader::getLocation(shader.loc_TexArray, shader.programId, "texArray");
            Engine::Shader::getLocation(shader.loc_FresnelPower, shader.programId, "fresnelPower");
            Engine::Shader::getLocation(shader.loc_FresnelScale, shader.programId, "fresnelScale");
            Engine::Shader::getLocation(shader.loc_FresnelBias, shader.programId, "fresnelBias");
        }

        void createShader(ShaderPlanet& shader) {

            std::string vertShader = "shader/lit_textured.vert";
            std::string fragShader = "shader/planet.frag";

            Engine::Shader::createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            Engine::Shader::bind(shader.programId);
            Engine::Shader::getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            Engine::Shader::getLocation(shader.loc_Model, shader.programId, "model");
            Engine::Shader::getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");

            Engine::Shader::getLocation(shader.loc_WaterScale, shader.programId, "waterScale");
            Engine::Shader::getLocation(shader.loc_AmountWater, shader.programId, "amountWater");
            Engine::Shader::getLocation(shader.loc_WaterPower, shader.programId, "waterPower");
            Engine::Shader::getLocation(shader.loc_WaterColor, shader.programId, "waterColor");
            Engine::Shader::getLocation(shader.loc_LandColor0, shader.programId, "landColor0");
            Engine::Shader::getLocation(shader.loc_LandColor1, shader.programId, "landColor1");
            Engine::Shader::getLocation(shader.loc_LandColorOverlay, shader.programId, "landColorOverlay");
            Engine::Shader::getLocation(shader.loc_LandColorPower, shader.programId, "landColorPower");
            
            Engine::Shader::getLocation(shader.loc_ContinentalShelfColor, shader.programId, "continentalShelfColor");
            Engine::Shader::getLocation(shader.loc_LightDirection, shader.programId, "lightDirection");
            Engine::Shader::getLocation(shader.loc_WaterContinentalShelf, shader.programId, "waterContinentalShelf");
            Engine::Shader::getLocation(shader.loc_WaterDepth, shader.programId, "waterDepth");
            Engine::Shader::getLocation(shader.loc_SurfaceTopologyScale, shader.programId, "surfaceTopologyScale");
            Engine::Shader::getLocation(shader.loc_LandColorBlendScale, shader.programId, "landColorBlendScale");
            
            Engine::Shader::getLocation(shader.loc_TexArray, shader.programId, "texArray");
            
            Engine::Shader::getLocation(shader.loc_MacroScale, shader.programId, "macroScale");
            Engine::Shader::getLocation(shader.loc_CloudScale, shader.programId, "cloudScale");
            Engine::Shader::getLocation(shader.loc_CloudPower, shader.programId, "cloudPower");
            Engine::Shader::getLocation(shader.loc_CloudOverlay, shader.programId, "cloudOverlay");
            Engine::Shader::getLocation(shader.loc_CloudOpacity, shader.programId, "cloudOpacity");
            Engine::Shader::getLocation(shader.loc_CloudColor, shader.programId, "cloudColor");
            Engine::Shader::getLocation(shader.loc_FresnelPowerClouds, shader.programId, "fresnelPowerClouds");
            Engine::Shader::getLocation(shader.loc_FresnelScaleClouds, shader.programId, "fresnelScaleClouds");
            Engine::Shader::getLocation(shader.loc_FresnelBiasClouds, shader.programId, "fresnelBiasClouds");
            Engine::Shader::getLocation(shader.loc_FresnelPowerAtmosphere, shader.programId, "fresnelPowerAtmosphere");
            Engine::Shader::getLocation(shader.loc_FresnelScaleAtmosphere, shader.programId, "fresnelScaleAtmosphere");
            Engine::Shader::getLocation(shader.loc_FresnelBiasAtmosphere, shader.programId, "fresnelBiasAtmosphere");
            
            Engine::Shader::getLocation(shader.loc_SpecularStrength, shader.programId, "specularStrength");
            Engine::Shader::getLocation(shader.loc_SpecularPower, shader.programId, "specularPower");
            
            Engine::Shader::getLocation(shader.loc_NoiseOctaveTexIndex0, shader.programId, "noiseOctaveTexIndex0");
            Engine::Shader::getLocation(shader.loc_NoiseOctaveTexIndex1, shader.programId, "noiseOctaveTexIndex1");

        }

        void updateUniforms(ShaderPlanet& shader, ShaderDataPlanet& shaderData) {

            Engine::Shader::bind(shader.programId);
            Engine::Shader::uniform(shader.loc_CameraPosition, shaderData.cameraPosition);
            Engine::Shader::uniform(shader.loc_ProjectionView, shaderData.projectionView);
            Engine::Shader::uniform(shader.loc_Model, shaderData.model);
            Engine::Shader::uniform(shader.loc_WaterScale, shaderData.waterScale);
            Engine::Shader::uniform(shader.loc_AmountWater, shaderData.amountWater);
            Engine::Shader::uniform(shader.loc_WaterPower, shaderData.waterPower);
            Engine::Shader::uniform(shader.loc_WaterColor, shaderData.waterColor);
            Engine::Shader::uniform(shader.loc_ContinentalShelfColor, shaderData.continentalShelfColor);
            Engine::Shader::uniform(shader.loc_WaterContinentalShelf, shaderData.waterContinentalShelf);
            Engine::Shader::uniform(shader.loc_WaterDepth, shaderData.waterDepth);
            Engine::Shader::uniform(shader.loc_LightDirection, shaderData.lightDirection);
            Engine::Shader::uniformTextureArray(shader.loc_TexArray, 0, shaderData.texArray);
            Engine::Shader::uniform(shader.loc_LandColor0, shaderData.landColor0);
            Engine::Shader::uniform(shader.loc_LandColor1, shaderData.landColor1);
            Engine::Shader::uniform(shader.loc_LandColorOverlay, shaderData.landColorOverlay);
            Engine::Shader::uniform(shader.loc_LandColorPower, shaderData.landColorPower);
            Engine::Shader::uniform(shader.loc_SurfaceTopologyScale, shaderData.surfaceTopologyScale);
            Engine::Shader::uniform(shader.loc_LandColorBlendScale, shaderData.landColorBlendScale);
            
            Engine::Shader::uniform(shader.loc_MacroScale, shaderData.macroScale);
            Engine::Shader::uniform(shader.loc_CloudScale, shaderData.cloudScale);
            Engine::Shader::uniform(shader.loc_CloudPower, shaderData.cloudPower);
            Engine::Shader::uniform(shader.loc_CloudOverlay, shaderData.cloudOverlay);
            Engine::Shader::uniform(shader.loc_CloudOpacity, shaderData.cloudOpacity);
            Engine::Shader::uniform(shader.loc_CloudColor, shaderData.cloudColor);
            Engine::Shader::uniform(shader.loc_FresnelPowerClouds, shaderData.fresnelPowerClouds);
            Engine::Shader::uniform(shader.loc_FresnelScaleClouds, shaderData.fresnelScaleClouds);
            Engine::Shader::uniform(shader.loc_FresnelBiasClouds, shaderData.fresnelBiasClouds);
            Engine::Shader::uniform(shader.loc_FresnelPowerAtmosphere, shaderData.fresnelPowerAtmosphere);
            Engine::Shader::uniform(shader.loc_FresnelScaleAtmosphere, shaderData.fresnelScaleAtmosphere);
            Engine::Shader::uniform(shader.loc_FresnelBiasAtmosphere, shaderData.fresnelBiasAtmosphere);
            Engine::Shader::uniform(shader.loc_SpecularStrength, shaderData.specularStrength);
            Engine::Shader::uniform(shader.loc_SpecularPower, shaderData.specularPower);
            
            Engine::Shader::uniform(shader.loc_NoiseOctaveTexIndex0, shaderData.noiseOctaveTexIndex0);
            Engine::Shader::uniform(shader.loc_NoiseOctaveTexIndex1, shaderData.noiseOctaveTexIndex1);

        }

        void updateUniforms(ShaderSun& shader, ShaderDataSun& shaderData) {

            Engine::Shader::bind(shader.programId);
            Engine::Shader::uniform(shader.loc_CameraPosition, shaderData.cameraPosition);
            Engine::Shader::uniform(shader.loc_ProjectionView, shaderData.projectionView);
            Engine::Shader::uniform(shader.loc_Model, shaderData.model);

            Engine::Shader::uniform(shader.loc_Color0, shaderData.color0);
            Engine::Shader::uniform(shader.loc_Color1, shaderData.color1);
            Engine::Shader::uniform(shader.loc_Color2, shaderData.color2);
            Engine::Shader::uniform(shader.loc_Color3, shaderData.color3);
            Engine::Shader::uniform(shader.loc_ColorOverlay0, shaderData.colorOverlay0);
            Engine::Shader::uniform(shader.loc_ColorOverlay1, shaderData.colorOverlay1);
            Engine::Shader::uniform(shader.loc_ColorPower0, shaderData.colorPower0);
            Engine::Shader::uniform(shader.loc_ColorPower1, shaderData.colorPower1);
            Engine::Shader::uniform(shader.loc_NoiseScale, shaderData.noiseScale);
            Engine::Shader::uniform(shader.loc_NoiseTexIndex, shaderData.noiseTexIndex);

            Engine::Shader::uniformTextureArray(shader.loc_TexArray, 0, shaderData.texArray);

            Engine::Shader::uniform(shader.loc_FresnelPower, shaderData.fresnelPower);
            Engine::Shader::uniform(shader.loc_FresnelScale, shaderData.fresnelScale);
            Engine::Shader::uniform(shader.loc_FresnelBias, shaderData.fresnelBias);
        }

        void updateUniforms(ShaderParticleSolarSystem& program, ShaderDataParticleSolarSystem& shaderData) {
            Engine::Shader::bind(program.programId);
            Engine::Shader::uniform(program.loc_ProjectionView, shaderData.projectionView);
            Engine::Shader::uniform(program.loc_CameraRight, shaderData.cameraRight);
            Engine::Shader::uniform(program.loc_CameraUp, shaderData.cameraUp);
            Engine::Shader::uniform(program.loc_AspectRatio, shaderData.aspectRatio);
            Engine::Shader::uniform(program.loc_CameraPosition, shaderData.cameraPosition);
            Engine::Shader::uniformTexture(program.loc_Tex, 0, shaderData.textureId);
        }

        //void updateUniforms(ShaderGrid& shaderProgram, glm::mat4& projectionView) {
        //    Engine::Shader::bind(shaderProgram.programId);
        //    Engine::Shader::uniform(shaderProgram.loc_ProjectionView, projectionView);
        //}

        void updateUniforms(ShaderTerrain& program, ShaderDataTerrain& shaderData) {
            Engine::Shader::bind(program.programId);
            Engine::Shader::uniform(program.loc_ProjectionView, shaderData.projectionView);
            Engine::Shader::uniform(program.loc_CameraPosition, shaderData.cameraPosition);
            Engine::Shader::uniform(program.loc_BlockSize, shaderData.blockSize);
        }

        void updateUniforms(ShaderFXAA& program, ShaderDataFXAA& shaderData) {
            Engine::Shader::bind(program.programId);
            Engine::Shader::uniformTexture(program.loc_Tex, 0, shaderData.textureId);
            Engine::Shader::uniform(program.loc_ScreenSize, shaderData.screenSize);
        }

    }

}
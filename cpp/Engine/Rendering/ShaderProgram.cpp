#include "pch.h"
#include "ShaderProgram.h"
#include "AssetManager.h"
#include "GraphicsApi.h"
#include "Texture2D.h"

namespace Engine {

    namespace Shader{

        void updateUniforms(ShaderTerrain& program, glm::mat4& projectionView, glm::vec3& cameraPosition, unsigned int blockSize) {
            bind(program.programId);
            uniform(program.loc_ProjectionView, projectionView);
            uniform(program.loc_CameraPosition, cameraPosition);
            uniform(program.loc_BlockSize, blockSize);
        }

        void updateUniforms(ShaderFXAA& program, unsigned int tex, glm::ivec2 screenSize) {
            bind(program.programId);
            uniformTexture(program.loc_Tex, 0, tex);
            uniform(program.loc_ScreenSize, screenSize);
        }


        void createShaderGalaxy(unsigned int& program){
            createShaderProgram(program, "shader/quad.vert", "shader/galaxy.frag");
            bind(program);
            //setTextureLocation(program, 0, "tex");
        }

        //void createShaderPhong(ShaderPhongTextured& program) {
        //    createShaderProgram(program.programId, "shader/lit_textured.vert", "shader/phong_textured.frag");
        //    bind(program.programId);
        //    getLocation(program.loc_View, program.programId, "view");
        //    getLocation(program.loc_Projection, program.programId, "projection");
        //    getLocation(program.loc_Model, program.programId, "model");
        //    getLocation(program.loc_CameraPosition, program.programId, "cameraPosition");
        //    getLocation(program.loc_Tex, program.programId, "tex");
        //}

        //void createShaderPhong(ShaderPhong& program) {
        //    createShaderProgram(program.programId, "shader/lit.vert", "shader/phong.frag");
        //    bind(program.programId);
        //    getLocation(program.loc_ProjectionView, program.programId, "projectionView");
        //    getLocation(program.loc_Model, program.programId, "model");
        //    getLocation(program.loc_CameraPosition, program.programId, "cameraPosition");
        //}

        void createShaderGrid(ShaderGrid& program) {
            createShaderProgram(program.programId, "shader/grid.vert", "shader/grid.frag");
            bind(program.programId);
            getLocation(program.loc_ProjectionView, program.programId, "projectionView");
        }

        void createShaderParticle(ShaderParticle& program) {

            std::string vertShader = "shader/particle/vert/particle.vert";
            std::string fragShader = "shader/particle/frag/particle_base.frag";

            createShaderProgram(program.programId, vertShader.c_str(), fragShader.c_str());
            bind(program.programId);
            getLocation(program.loc_ProjectionView, program.programId, "projectionView");
            getLocation(program.loc_CameraRight, program.programId, "cameraRight");
            getLocation(program.loc_CameraUp, program.programId, "cameraUp");
        }

        void createShaderParticle(ShaderParticleTextured& program) {

            std::string vertShader = "shader/particle/vert/particle.vert";
            std::string fragShader = "shader/particle/frag/particle_texture.frag";

            createShaderProgram(program.programId, vertShader.c_str(), fragShader.c_str());
            bind(program.programId);
            getLocation(program.loc_ProjectionView, program.programId, "projectionView");
            getLocation(program.loc_CameraRight, program.programId, "cameraRight");
            getLocation(program.loc_CameraUp, program.programId, "cameraUp");
            getLocation(program.loc_Tex, program.programId, "tex");
        }

        void createShaderParticleSolarSystem(ShaderParticleSolarSystem& shader) {

            std::string vertShader = "shader/particle/vert/particle_solar_system.vert";
            std::string fragShader = "shader/particle/frag/particle_base.frag";

            createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            bind(shader.programId);
            getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            getLocation(shader.loc_CameraRight, shader.programId, "cameraRight");
            getLocation(shader.loc_CameraUp, shader.programId, "cameraUp");
            getLocation(shader.loc_AspectRatio, shader.programId, "aspectRatio");
        }

        void createShaderTerrain(ShaderTerrain& shader) {

            std::string vertShader = "shader/terrain/terrain.vert";
            std::string fragShader = "shader/terrain/terrain.frag";

            createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            bind(shader.programId);
            getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");
            getLocation(shader.loc_BlockSize, shader.programId, "blockSize");
        }

        void createShaderFXAA(ShaderFXAA& shader) {

            std::string vertShader = "shader/quad.vert";
            std::string fragShader = "shader/postprocess/fxaa.frag";

            createShaderProgram(shader.programId, vertShader.c_str(), fragShader.c_str());
            bind(shader.programId);
            getLocation(shader.loc_Tex, shader.programId, "tex");
            getLocation(shader.loc_ScreenSize, shader.programId, "screenSize");
        }

        void createShaderPlanet(PlanetShader& shader) {
            createShaderPlanet(shader, "shader/lit_textured.vert", "shader/planet.frag");
        }

        void createShaderSun(ShaderSun& shader) {

            createShaderProgram(shader.programId, "shader/lit_textured.vert", "shader/sun.frag");
            bind(shader.programId);

            getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            getLocation(shader.loc_Model, shader.programId, "model");
        }

        
        void createShaderPlanet(PlanetShader& shader, const char* vert, const char* frag) {
            createShaderProgram(shader.programId, vert, frag);
            bind(shader.programId);
            getLocation(shader.loc_ProjectionView, shader.programId, "projectionView");
            getLocation(shader.loc_Model, shader.programId, "model");
            getLocation(shader.loc_CameraPosition, shader.programId, "cameraPosition");

            getLocation(shader.loc_WaterScale, shader.programId, "waterScale");
            getLocation(shader.loc_AmountWater, shader.programId, "amountWater");
            getLocation(shader.loc_WaterPower, shader.programId, "waterPower");
            getLocation(shader.loc_WaterColor, shader.programId, "waterColor");
            getLocation(shader.loc_LandColor0, shader.programId, "landColor0");
            getLocation(shader.loc_LandColor1, shader.programId, "landColor1");
            getLocation(shader.loc_LandColorOverlay, shader.programId, "landColorOverlay");
            getLocation(shader.loc_LandColorPower, shader.programId, "landColorPower");

            getLocation(shader.loc_ContinentalShelfColor, shader.programId, "continentalShelfColor");
            getLocation(shader.loc_LightDirection, shader.programId, "lightDirection");
            getLocation(shader.loc_WaterContinentalShelf, shader.programId, "waterContinentalShelf");
            getLocation(shader.loc_WaterDepth, shader.programId, "waterDepth");
            getLocation(shader.loc_SurfaceTopologyScale, shader.programId, "surfaceTopologyScale");
            getLocation(shader.loc_LandColorBlendScale, shader.programId, "landColorBlendScale");

            getLocation(shader.loc_TexArray, shader.programId, "texArray");

            getLocation(shader.loc_MacroScale, shader.programId, "macroScale");
            getLocation(shader.loc_CloudScale, shader.programId, "cloudScale");
            getLocation(shader.loc_CloudPower, shader.programId, "cloudPower");
            getLocation(shader.loc_CloudOverlay, shader.programId, "cloudOverlay");
            getLocation(shader.loc_CloudOpacity, shader.programId, "cloudOpacity");
            getLocation(shader.loc_CloudColor, shader.programId, "cloudColor");
            getLocation(shader.loc_FresnelPowerClouds, shader.programId, "fresnelPowerClouds");
            getLocation(shader.loc_FresnelScaleClouds, shader.programId, "fresnelScaleClouds");
            getLocation(shader.loc_FresnelBiasClouds, shader.programId, "fresnelBiasClouds");
            getLocation(shader.loc_FresnelPowerAtmosphere, shader.programId, "fresnelPowerAtmosphere");
            getLocation(shader.loc_FresnelScaleAtmosphere, shader.programId, "fresnelScaleAtmosphere");
            getLocation(shader.loc_FresnelBiasAtmosphere, shader.programId, "fresnelBiasAtmosphere");

            getLocation(shader.loc_SpecularStrength, shader.programId, "specularStrength");
            getLocation(shader.loc_SpecularPower, shader.programId, "specularPower");

            getLocation(shader.loc_NoiseOctaveTexIndex0, shader.programId, "noiseOctaveTexIndex0");
            getLocation(shader.loc_NoiseOctaveTexIndex1, shader.programId, "noiseOctaveTexIndex1");

        }

        void updateUniforms(PlanetShader& shader, PlanetShaderData& planetShaderData) {

            bind(shader.programId);
            uniform(shader.loc_CameraPosition, planetShaderData.cameraPosition);
            uniform(shader.loc_ProjectionView, planetShaderData.projectionView);
            uniform(shader.loc_Model, planetShaderData.model);
            uniform(shader.loc_WaterScale, planetShaderData.waterScale);
            uniform(shader.loc_AmountWater, planetShaderData.amountWater);
            uniform(shader.loc_WaterPower, planetShaderData.waterPower);
            uniform(shader.loc_WaterColor, planetShaderData.waterColor);
            uniform(shader.loc_ContinentalShelfColor, planetShaderData.continentalShelfColor);
            uniform(shader.loc_WaterContinentalShelf, planetShaderData.waterContinentalShelf);
            uniform(shader.loc_WaterDepth, planetShaderData.waterDepth);
            uniform(shader.loc_LightDirection, planetShaderData.lightDirection);
            uniformTextureArray(shader.loc_TexArray, 0, planetShaderData.texArray);
            uniform(shader.loc_LandColor0, planetShaderData.landColor0);
            uniform(shader.loc_LandColor1, planetShaderData.landColor1);
            uniform(shader.loc_LandColorOverlay, planetShaderData.landColorOverlay);
            uniform(shader.loc_LandColorPower, planetShaderData.landColorPower);
            uniform(shader.loc_SurfaceTopologyScale, planetShaderData.surfaceTopologyScale);
            uniform(shader.loc_LandColorBlendScale, planetShaderData.landColorBlendScale);

            uniform(shader.loc_MacroScale, planetShaderData.macroScale);
            uniform(shader.loc_CloudScale, planetShaderData.cloudScale);
            uniform(shader.loc_CloudPower, planetShaderData.cloudPower);
            uniform(shader.loc_CloudOverlay, planetShaderData.cloudOverlay);
            uniform(shader.loc_CloudOpacity, planetShaderData.cloudOpacity);
            uniform(shader.loc_CloudColor, planetShaderData.cloudColor);
            uniform(shader.loc_FresnelPowerClouds, planetShaderData.fresnelPowerClouds);
            uniform(shader.loc_FresnelScaleClouds, planetShaderData.fresnelScaleClouds);
            uniform(shader.loc_FresnelBiasClouds, planetShaderData.fresnelBiasClouds);
            uniform(shader.loc_FresnelPowerAtmosphere, planetShaderData.fresnelPowerAtmosphere);
            uniform(shader.loc_FresnelScaleAtmosphere, planetShaderData.fresnelScaleAtmosphere);
            uniform(shader.loc_FresnelBiasAtmosphere, planetShaderData.fresnelBiasAtmosphere);
            uniform(shader.loc_SpecularStrength, planetShaderData.specularStrength);
            uniform(shader.loc_SpecularPower, planetShaderData.specularPower);

            uniform(shader.loc_NoiseOctaveTexIndex0, planetShaderData.noiseOctaveTexIndex0);
            uniform(shader.loc_NoiseOctaveTexIndex1, planetShaderData.noiseOctaveTexIndex1);

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

        void uniformTexture(unsigned int location, unsigned int slot, unsigned int textureId) {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glUniform1i(location, slot);
        }

        void uniformTextureArray(unsigned int location, unsigned int slot, unsigned int textureId) {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
            glUniform1i(location, slot);
        }

        void setTextureLocation(unsigned int& shaderProgramId, unsigned int index, const char* uniformName) {
            unsigned int texLocation;
            getLocation(texLocation, shaderProgramId, uniformName);
            uniform(texLocation, index);
        }

        void getLocation(unsigned int& location, unsigned int shaderProgramId, const char* uniformName){
            location = glGetUniformLocation(shaderProgramId, uniformName);
        }

    }

}
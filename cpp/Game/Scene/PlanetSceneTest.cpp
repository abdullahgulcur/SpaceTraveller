#include "pch.h"
#include "PlanetSceneTest.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
//#include "Core.h"
#include "VertexBuffer.h"
#include "RandomValue.h"
#include "AssetManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Game {

    void PlanetSceneTest::init() {

    }

    void PlanetSceneTest::parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer) {
        
        std::string text(buffer.begin(), buffer.end());
        std::istringstream stream(text);
        std::string line;

        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            int r0, g0, b0, r1, g1, b1, r2, g2, b2, r3, g3, b3;

            linestream >> r0 >> g0 >> b0 >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3;

            PlanetColors colors;
            colors.landA = glm::u8vec3(r0, g0, b0);
            colors.landB = glm::u8vec3(r1, g1, b1);
            colors.sea = glm::u8vec3(r2, g2, b2);
            colors.shelf = glm::u8vec3(r3, g3, b3);

            planetColors.push_back(colors);
        }
    }

    void PlanetSceneTest::start() {

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(Game::getInstance()->appSurface.glfwContext.GLFW_window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        std::vector<unsigned char> buffer;
        Engine::AssetManager assetManager;
        assetManager.readBytesFromAsset("data/planet_color_records.txt", buffer);
        PlanetSceneTest::parsePlanetColors(planetColors, buffer);
    }

    void PlanetSceneTest::update(float dt) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Planet Properties");
        ImGui::Text("Parameters");

        ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;
        ImGui::ColorEdit3("Water Color", (float*)&waterColor, base_flags);
        //ImGui::ColorEdit3("Continental Shelf Color", (float*)&continentalShelfColor, base_flags);
        ImGui::DragFloat("Amount Water", &amountWater, 0.01f, 0.0f, 0.8f);

        ImGui::DragInt("Tex Index 0", &noiseOctaveTexIndex0, 0.01f, 0, 6);
        ImGui::DragInt("Tex Index 1", &noiseOctaveTexIndex1, 0.01f, 0, 6);

        ImGui::DragFloat("Continental Shelf", &continentalShelf, 0.01f, 0.f, 0.1f);
        ImGui::ColorEdit3("Land Color 0", (float*)&landColor0, base_flags);
        ImGui::ColorEdit3("Land Color 1", (float*)&landColor1, base_flags);
        ImGui::DragFloat("Land Color Overlay", &landColorOverlay, 0.01f, 1.f, 2.f);
        ImGui::DragFloat("Land Color Power", &landColorPower, 0.01f, 1.f, 10.f);
        ImGui::DragFloat("Surface Topology Scale", &surfaceTopologyScale, 0.01f, 0.1f, 1.f);
        ImGui::DragFloat("Land Color Blend Scale", &landColorBlendScale, 0.01f, 0.25f, 1.5f);

        //ImGui::ColorEdit3("Cloud Color", (float*)&cloudColor, base_flags);
        ImGui::DragFloat("Macro Scale", &macroScale, 0.01f, 5.0f, 12.0f);
        /*ImGui::DragFloat("Cloud Scale", &cloudScale, 0.01f, 1.f, 2.f);
        ImGui::DragFloat("Cloud Power", &cloudPower, 0.1f, 7.0f, 20.f);
        ImGui::DragFloat("Cloud Overlay", &cloudOverlay, 0.01f, 0.f, 4.0f);
        ImGui::DragFloat("Cloud Opacity", &cloudOpacity, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Power Clouds", &fresnelPowerClouds, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Scale Clouds", &fresnelScaleClouds, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Bias Clouds", &fresnelBiasClouds, 0.01f, 0.f, 1.f);*/

        /*ImGui::DragFloat("Fresnel Power Atmosphere", &fresnelPowerAtmosphere, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Scale Atmosphere", &fresnelScaleAtmosphere, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Bias Atmosphere", &fresnelBiasAtmosphere, 0.01f, 0.f, 1.f);*/

        //ImGui::DragFloat("Specular Strength", &specularStrength, 0.01f, 0.f, 10.f);
        //ImGui::DragFloat("Specular Power", &specularPower, 0.01f, 0.f, 100.f);


        if (ImGui::Button("Randomize")) {

            PlanetColors& colors = planetColors[Engine::Random::random(0, planetColors.size() - 1)];
            landColor0 = glm::vec3(colors.landA) / glm::vec3(255.f);
            landColor1 = glm::vec3(colors.landB) / glm::vec3(255.f);

            waterColor = glm::vec3(colors.sea) / glm::vec3(255.f);
            continentalShelfColor = glm::vec3(colors.shelf) / glm::vec3(255.f);


            /*waterColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
            continentalShelfColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));

            landColor0 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
            landColor1 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));*/

            amountWater = Engine::Random::randomFloat(0.f, 0.8f);
            continentalShelf = 0.04f;
            landColorOverlay = Engine::Random::randomFloat(1.f, 2.f);
            landColorPower = Engine::Random::randomFloat(1.f, 10.f);
            surfaceTopologyScale = Engine::Random::randomFloat(0.1f, 1.f);
            landColorBlendScale = Engine::Random::randomFloat(0.25f, 1.5f);
            macroScale = Engine::Random::randomFloat(5.f, 12.f);
            cloudScale = Engine::Random::randomFloat(1.f, 2.f);
            cloudPower = Engine::Random::randomFloat(7.f, 20.f);
            cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);
            //cloudOpacity = Engine::Random::randomFloat(0.f, 1.f);
            fresnelPowerClouds = 0.3f;
            fresnelScaleClouds = 0.2f;
            fresnelBiasClouds = 1.f;
            
            //fresnelPowerAtmosphere = 0.8f;// Engine::Random::randomFloat(0.0f, 1.f);
            //fresnelScaleAtmosphere = 0.15f;// Engine::Random::randomFloat(0.0f, 1.f);
            //fresnelBiasAtmosphere = 1.f;// Engine::Random::randomFloat(0.0f, 1.f);

            noiseOctaveTexIndex0 = Engine::Random::random(0, 6);
            noiseOctaveTexIndex1 = Engine::Random::random(0, 6);
            //noiseOctaveTexIndex2 = Engine::Random::random(0, 1);
        }

        ImGui::End();

        ImGui::Render();

        //---------

        //Engine::Core* core = Engine::Core::getInstance();
        //Game* game = Game::getInstance();
        //Engine::Input& input = core->input;
        //Engine::Camera::Camera& camera = game->camera;

        //if (input.getPointerDown() && input.getButtonDown(Engine::InputCode::Space)) {
        //    float deltaX = input.getPointerDelta().x * 0.01f;
        //    float deltaY = -input.getPointerDelta().y * 0.01f;
        //    cameraCtrl.ProcessInput(deltaX, deltaY, 0.f);
        //}

        //cameraCtrl.Update(dt);

        //Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        //game->sceneFrame.activate();

        //Engine::Shader::PlanetShaderData planetShaderData;
        //planetShaderData.cameraPosition = camera.position;
        //planetShaderData.projectionView = camera.projectionView;
        //planetShaderData.model = glm::translate(glm::mat4(1), glm::vec3(0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
        //planetShaderData.waterColor = waterColor;
        //planetShaderData.amountWater = amountWater;
        //planetShaderData.continentalShelfColor = continentalShelfColor;
        //planetShaderData.waterContinentalShelf = continentalShelf;
        //planetShaderData.lightDirection = glm::normalize(glm::vec3(1, 0, 1));
        //planetShaderData.landColor0 = landColor0;
        //planetShaderData.landColor1 = landColor1;
        //planetShaderData.landColorOverlay = landColorOverlay;
        //planetShaderData.landColorPower = landColorPower;
        //planetShaderData.surfaceTopologyScale = surfaceTopologyScale;
        //planetShaderData.landColorBlendScale = landColorBlendScale;
        //planetShaderData.tex0 = game->assetGenerator.perlinTextureId;
        //planetShaderData.tex1 = game->assetGenerator.macroTextureId;
        //planetShaderData.texArray = game->assetGenerator.noiseTextureArrayId;

        //planetShaderData.macroScale = macroScale;
        //planetShaderData.cloudScale = cloudScale;
        //planetShaderData.cloudPower = cloudPower;
        //planetShaderData.cloudOverlay = cloudOverlay;
        //planetShaderData.cloudOpacity = cloudOpacity;
        //planetShaderData.cloudColor = cloudColor;
        //planetShaderData.fresnelPowerClouds = fresnelPowerClouds;
        //planetShaderData.fresnelScaleClouds = fresnelScaleClouds;
        //planetShaderData.fresnelBiasClouds = fresnelBiasClouds;
        //planetShaderData.fresnelPowerAtmosphere = fresnelPowerAtmosphere;
        //planetShaderData.fresnelScaleAtmosphere = fresnelScaleAtmosphere;
        //planetShaderData.fresnelBiasAtmosphere = fresnelBiasAtmosphere;
        //planetShaderData.specularStrength = specularStrength;
        //planetShaderData.specularPower = specularPower;

        //planetShaderData.noiseOctaveTexIndex0 = float(noiseOctaveTexIndex0);
        //planetShaderData.noiseOctaveTexIndex1 = float(noiseOctaveTexIndex1);
        //planetShaderData.noiseOctaveTexIndex2 = float(noiseOctaveTexIndex2);

        //Engine::Shader::updateUniforms(game->assetGenerator.planetShader, planetShaderData);



        ////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);
        ////glPolygonMode(GL_BACK, GL_FILL);

        //game->sceneFrame.postProcess();

        //---------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
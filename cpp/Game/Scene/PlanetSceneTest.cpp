#include "pch.h"
#include "PlanetSceneTest.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"
#include "VertexBuffer.h"
#include "RandomValue.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Game {

    void PlanetSceneTest::init() {

    }

    void PlanetSceneTest::start() {

        Engine::Core* core = Engine::Core::getInstance();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(core->appSurface.glfwContext.GLFW_window, true);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void PlanetSceneTest::update(float dt) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Planet Properties");
        ImGui::Text("Parameters");

        ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;
        ImGui::ColorEdit3("Water Color", (float*)&waterColor, base_flags);
        ImGui::ColorEdit3("Continental Shelf Color", (float*)&continentalShelfColor, base_flags);
        ImGui::DragFloat("Amount Water", &amountSea, 0.01f, 0.0f, 1.f);

        ImGui::DragInt("Tex Index 0", &noiseOctaveTexIndex0, 0.01f, 0, 1);
        ImGui::DragInt("Tex Index 1", &noiseOctaveTexIndex1, 0.01f, 0, 1);
        ImGui::DragInt("Tex Index 2", &noiseOctaveTexIndex2, 0.01f, 0, 1);

        ImGui::DragFloat("Continental Shelf", &continentalShelf, 0.01f, 0.f, 0.1f);
        ImGui::ColorEdit3("Land Color 0", (float*)&landColor0, base_flags);
        ImGui::ColorEdit3("Land Color 1", (float*)&landColor1, base_flags);
        ImGui::DragFloat("Land Color Overlay", &landColorOverlay, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Land Color Power", &landColorPower, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Surface Topology Scale", &surfaceTopologyScale, 0.01f, 0.f, 3.f);
        ImGui::DragFloat("Land Color Blend Scale", &landColorBlendScale, 0.01f, 0.1f, 5.f);

        ImGui::ColorEdit3("Cloud Color", (float*)&cloudColor, base_flags);
        ImGui::DragFloat("Macro Scale", &macroScale, 0.01f, 0.5f, 5.f);
        ImGui::DragFloat("Cloud Scale", &cloudScale, 0.01f, 1.f, 2.f);
        ImGui::DragFloat("Cloud Power", &cloudPower, 0.1f, 7.0f, 20.f);
        ImGui::DragFloat("Cloud Overlay", &cloudOverlay, 0.01f, 0.f, 4.0f);
        ImGui::DragFloat("Cloud Opacity", &cloudOpacity, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Power Clouds", &fresnelPowerClouds, 0.01f, 0.f, 0.15f);
        ImGui::DragFloat("Fresnel Scale Clouds", &fresnelScaleClouds, 0.01f, 0.f, 0.3f);
        //ImGui::DragFloat("Fresnel Bias Clouds", &fresnelBiasClouds, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Fresnel Power Atmosphere", &fresnelPowerAtmosphere, 0.01f, 0.6f, 0.75f);
        ImGui::DragFloat("Fresnel Scale Atmosphere", &fresnelScaleAtmosphere, 0.01f, 0.9f, 1.f);
        ImGui::DragFloat("Fresnel Bias Atmosphere", &fresnelBiasAtmosphere, 0.01f, 0.9f, 0.95f);

        if (ImGui::Button("Randomize")) {
            /*waterColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
            continentalShelfColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));*/

            landColor0 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
            landColor1 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));

            /*landColor0 = glm::vec3(0.6, 0.25, 0.1);
            landColor1 = glm::vec3(0.4, 0.2, 0.1);*/

            amountSea = Engine::Random::randomFloat(0.f, 1.f);
            continentalShelf = Engine::Random::randomFloat(0.f, 0.1f);
            landColorOverlay = Engine::Random::randomFloat(0.f, 10.f);
            landColorPower = Engine::Random::randomFloat(0.f, 10.f);
            surfaceTopologyScale = Engine::Random::randomFloat(0.f, 3.f);
            landColorBlendScale = Engine::Random::randomFloat(0.1f, 5.f);
            macroScale = Engine::Random::randomFloat(0.5f, 5.f);
            cloudScale = Engine::Random::randomFloat(1.f, 2.f);
            cloudPower = Engine::Random::randomFloat(7.f, 20.f);
            cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);
            //cloudOpacity = Engine::Random::randomFloat(0.f, 1.f);
            fresnelPowerClouds = Engine::Random::randomFloat(0.f, 0.15f);
            fresnelScaleClouds = Engine::Random::randomFloat(0.f, 0.3f);
            fresnelPowerAtmosphere = Engine::Random::randomFloat(0.6f, 0.75f);
            fresnelScaleAtmosphere = Engine::Random::randomFloat(0.9f, 1.f);
            fresnelBiasAtmosphere = Engine::Random::randomFloat(0.9f, 0.95f);

            noiseOctaveTexIndex0 = Engine::Random::random(0, 1);
            noiseOctaveTexIndex1 = Engine::Random::random(0, 1);
            noiseOctaveTexIndex2 = Engine::Random::random(0, 1);
        }

        ImGui::End();

        ImGui::Render();

        //---------

        Engine::Core* core = Engine::Core::getInstance();
        Game* game = Game::getInstance();
        Engine::Input& input = core->input;
        Engine::Camera::Camera& camera = game->camera;

        if (input.getPointerDown() && input.getButtonDown(Engine::InputCode::Space)) {
            float deltaX = input.getPointerDelta().x * 0.01f;
            float deltaY = -input.getPointerDelta().y * 0.01f;
            cameraCtrl.ProcessInput(deltaX, deltaY, 0.f);
        }

        cameraCtrl.Update(dt);

        Engine::Camera::lookAt(camera, cameraCtrl.m_position, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));

        Engine::FrameBuffer::refreshScreen();

        Engine::Shader::PlanetShaderData planetShaderData;
        planetShaderData.cameraPosition = camera.position;
        planetShaderData.projectionView = camera.projectionView;
        planetShaderData.model = glm::translate(glm::mat4(1), glm::vec3(0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
        planetShaderData.waterColor = waterColor;
        planetShaderData.waterTreshold = amountSea;
        planetShaderData.continentalShelfColor = continentalShelfColor;
        planetShaderData.waterContinentalShelf = continentalShelf;
        planetShaderData.lightDirection = glm::normalize(glm::vec3(1, 0, 1));
        planetShaderData.landColor0 = landColor0;
        planetShaderData.landColor1 = landColor1;
        planetShaderData.landColorOverlay = landColorOverlay;
        planetShaderData.landColorPower = landColorPower;
        planetShaderData.surfaceTopologyScale = surfaceTopologyScale;
        planetShaderData.landColorBlendScale = landColorBlendScale;
        planetShaderData.tex0 = game->perlinTextureId;
        planetShaderData.tex1 = game->macroTextureId;
        planetShaderData.texArray = game->noiseTextureArrayId;

        planetShaderData.macroScale = macroScale;
        planetShaderData.cloudScale = cloudScale;
        planetShaderData.cloudPower = cloudPower;
        planetShaderData.cloudOverlay = cloudOverlay;
        planetShaderData.cloudOpacity = cloudOpacity;
        planetShaderData.cloudColor = cloudColor;
        planetShaderData.fresnelPowerClouds = fresnelPowerClouds;
        planetShaderData.fresnelScaleClouds = fresnelScaleClouds;
        planetShaderData.fresnelBiasClouds = fresnelBiasClouds;
        planetShaderData.fresnelPowerAtmosphere = fresnelPowerAtmosphere;
        planetShaderData.fresnelScaleAtmosphere = fresnelScaleAtmosphere;
        planetShaderData.fresnelBiasAtmosphere = fresnelBiasAtmosphere;

        planetShaderData.noiseOctaveTexIndex0 = float(noiseOctaveTexIndex0);
        planetShaderData.noiseOctaveTexIndex1 = float(noiseOctaveTexIndex1);
        planetShaderData.noiseOctaveTexIndex2 = float(noiseOctaveTexIndex2);

        Engine::Shader::updateUniforms(game->planetShader, planetShaderData);
        Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);

        //---------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
#include "pch.h"
#include "PlanetSceneTest.h"
#include "DrawCommand.h"
#include "FrameBuffer.h"
#include "Game.h"
#include "Vao.h"
#include "Core.h"
#include "VertexBuffer.h"

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
        ImGui::DragFloat("Amount Water", &amountSea, 0.01f, 0.f, 1.f);
        ImGui::DragFloat("Continental Shelf", &continentalShelf, 0.01f, 0.f, 1.f);
        ImGui::ColorEdit3("Land Color 0", (float*)&landColor0, base_flags);
        ImGui::ColorEdit3("Land Color 1", (float*)&landColor1, base_flags);
        ImGui::DragFloat("Land Color Overlay", &landColorOverlay, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Land Color Power", &landColorPower, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Surface Topology Scale", &surfaceTopologyScale, 0.01f, 0.f, 3.f);
        ImGui::DragFloat("Land Color Blend Scale", &landColorBlendScale, 0.01f, 0.f, 5.f);

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
        planetShaderData.model = glm::translate(glm::mat4(1), glm::vec3(0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(3.f));
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

        Engine::Shader::updateUniforms(game->planetShader, planetShaderData);
        Engine::DrawCommand::draw(game->vaoSphereMesh, game->sphereMeshData.indexBuffer.totalIndices, game->sphereMeshData.indexBuffer.indexElementType);

        //---------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
#include "pch.h"
#include "SunSceneTest.h"
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

    void SunSceneTest::init() {

    }

    //void SunSceneTest::parsePlanetColors(std::vector<PlanetColors>& planetColors, const std::vector<unsigned char>& buffer) {
    //    
    //    std::string text(buffer.begin(), buffer.end());
    //    std::istringstream stream(text);
    //    std::string line;

    //    while (std::getline(stream, line)) {
    //        std::istringstream linestream(line);
    //        int r0, g0, b0, r1, g1, b1, r2, g2, b2, r3, g3, b3;

    //        linestream >> r0 >> g0 >> b0 >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3;

    //        PlanetColors colors;
    //        colors.landA = glm::u8vec3(r0, g0, b0);
    //        colors.landB = glm::u8vec3(r1, g1, b1);
    //        colors.sea = glm::u8vec3(r2, g2, b2);
    //        colors.shelf = glm::u8vec3(r3, g3, b3);

    //        planetColors.push_back(colors);
    //    }
    //}

    void SunSceneTest::start() {

        //Engine::Core* core = Engine::Core::getInstance();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        ImGui::StyleColorsDark();
        //ImGui_ImplGlfw_InitForOpenGL(Game::getInstance()->appSurface.glfwContext.GLFW_window, true);
        //ImGui_ImplOpenGL3_Init("#version 460");

        //std::vector<unsigned char> buffer;
        //Engine::AssetManager assetManager;
        //assetManager.readBytesFromAsset("data/planet_color_records.txt", buffer);
        //SunSceneTest::parsePlanetColors(planetColors, buffer);
    }

    void SunSceneTest::update(float dt) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Sun Properties");
        ImGui::Text("Parameters");

        ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

        ImGui::ColorEdit3("Color 0", (float*)&color0, base_flags);
        ImGui::ColorEdit3("Color 1", (float*)&color1, base_flags);
        ImGui::ColorEdit3("Color 2", (float*)&color2, base_flags);
        ImGui::ColorEdit3("Color 3", (float*)&color3, base_flags);

        ImGui::DragInt("Noise Tex Index", &noiseTexIndex, 0.01f, 0, 6);

        ImGui::DragFloat("Color Overlay 0", &colorOverlay0, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Color Overlay 1", &colorOverlay1, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Color Power 0", &colorPower0, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Color Power 1", &colorPower1, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Noise Scale", &noiseScale, 0.01f, 0.1f, 5.0f);
        ImGui::DragFloat("Fresnel Power", &fresnelPower, 0.01f, 0.1f, 1.0f);
        ImGui::DragFloat("Fresnel Scale", &fresnelScale, 0.01f, 0.1f, 1.0f);
        ImGui::DragFloat("Fresnel Bias", &fresnelBias, 0.01f, 0.1f, 1.0f);

        if (ImGui::Button("Randomize")) {



        //    //PlanetColors& colors = planetColors[Engine::Random::random(0, planetColors.size() - 1)];
        //    //landColor0 = glm::vec3(colors.landA) / glm::vec3(255.f);
        //    //landColor1 = glm::vec3(colors.landB) / glm::vec3(255.f);

        //    //waterColor = glm::vec3(colors.sea) / glm::vec3(255.f);
        //    //continentalShelfColor = glm::vec3(colors.shelf) / glm::vec3(255.f);


        //    ///*waterColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
        //    //continentalShelfColor = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));

        //    //landColor0 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));
        //    //landColor1 = Engine::Random::randomVec3(glm::vec3(0.f), glm::vec3(1.f));*/

        //    //amountWater = Engine::Random::randomFloat(0.f, 0.8f);
        //    //continentalShelf = 0.04f;
        //    //landColorOverlay = Engine::Random::randomFloat(1.f, 2.f);
        //    //landColorPower = Engine::Random::randomFloat(1.f, 10.f);
        //    //surfaceTopologyScale = Engine::Random::randomFloat(0.1f, 1.f);
        //    //landColorBlendScale = Engine::Random::randomFloat(0.25f, 1.5f);
        //    //macroScale = Engine::Random::randomFloat(5.f, 12.f);
        //    //cloudScale = Engine::Random::randomFloat(1.f, 2.f);
        //    //cloudPower = Engine::Random::randomFloat(7.f, 20.f);
        //    //cloudOverlay = Engine::Random::randomFloat(0.f, 4.f);
        //    ////cloudOpacity = Engine::Random::randomFloat(0.f, 1.f);
        //    //fresnelPowerClouds = 0.3f;
        //    //fresnelScaleClouds = 0.2f;
        //    //fresnelBiasClouds = 1.f;
        //    //
        //    ////fresnelPowerAtmosphere = 0.8f;// Engine::Random::randomFloat(0.0f, 1.f);
        //    ////fresnelScaleAtmosphere = 0.15f;// Engine::Random::randomFloat(0.0f, 1.f);
        //    ////fresnelBiasAtmosphere = 1.f;// Engine::Random::randomFloat(0.0f, 1.f);

        //    //noiseOctaveTexIndex0 = Engine::Random::random(0, 6);
        //    //noiseOctaveTexIndex1 = Engine::Random::random(0, 6);
        //    ////noiseOctaveTexIndex2 = Engine::Random::random(0, 1);
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

        //Engine::Shader::ShaderDataSun shaderData;
        //shaderData.cameraPosition = camera.position;
        //shaderData.projectionView = camera.projectionView;
        //shaderData.model = glm::translate(glm::mat4(1), glm::vec3(0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
        //shaderData.color0 = color0;
        //shaderData.color1 = color1;
        //shaderData.color2 = color2;
        //shaderData.color3 = color3;
        //shaderData.colorOverlay0 = colorOverlay0;
        //shaderData.colorOverlay1 = colorOverlay1;
        //shaderData.colorPower0 = colorPower0;
        //shaderData.colorPower1 = colorPower1;
        //shaderData.noiseScale = noiseScale;
        //shaderData.noiseTexIndex = float(noiseTexIndex);
        //shaderData.texArray = game->assetGenerator.noiseTextureArrayId;
        //shaderData.fresnelPower = fresnelPower;
        //shaderData.fresnelScale = fresnelScale;
        //shaderData.fresnelBias = fresnelBias;

        //Engine::Shader::updateUniforms(game->assetGenerator.shaderSun, shaderData);

        //Engine::DrawCommand::draw(game->assetGenerator.vaoSphereMesh, game->assetGenerator.sphereMeshData.indexBuffer.totalIndices, game->assetGenerator.sphereMeshData.indexBuffer.indexElementType);

        //game->sceneFrame.postProcess();

        //---------
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}
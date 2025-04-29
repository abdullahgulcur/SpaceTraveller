#include "pch.h"
#include "Camera.h"
#include "CameraController.h"
#include "Core.h"

namespace Game{

    void CameraController::init(Engine::Camera::Camera& camera){

        Engine::Core* core = Engine::Core::getInstance();

        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);
    }

    void CameraController::update(Engine::Camera::Camera& camera, float dt){

        Engine::Core* core = Engine::Core::getInstance();
        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->eglContext.width_ / (float)core->eglContext.height_, 0.1f, 1000.0f);

        targetHorizontalAngle += -core->input.pointerDelta.x * 0.01;
        horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
        float radius = 30;
        camera.position = glm::vec3(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
        Engine::Camera::view(camera.view, camera.position, glm::vec3(0));
    }

}
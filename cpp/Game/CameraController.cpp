#include "pch.h"
#include "CameraController.h""
#include "gtc/matrix_transform.hpp"

namespace Game{

    void CameraController::setTargetPosition(const glm::vec3& pos) {
        targetTransform.position = pos;
    }

    void CameraController::setTargetPitch(float p) {
        targetTransform.pitch = p;
        clampAngles();
    }

    void CameraController::setTargetYaw(float y) {
        targetTransform.yaw = y;
    }

    void CameraController::addTargetPitch(float delta) {
        targetTransform.pitch += delta;
        clampAngles();
    }

    void CameraController::addTargetYaw(float delta) {
        targetTransform.yaw += delta;
    }

    void CameraController::setTransform(Engine::Camera::CameraTransform& transform) {
        currentTransform = transform;
        targetTransform = transform;
    }


    void CameraController::init(Engine::Camera::CameraTransform transform) {
        currentTransform = transform;
        targetTransform = transform;
        CameraController::clampAngles();
    }


    void CameraController::update(float deltaTime) {
        float posLerpFactor = 1.0f - expf(-positionSmoothness * deltaTime);
        float rotLerpFactor = 1.0f - expf(-rotationSmoothness * deltaTime);

        posLerpFactor = glm::clamp(posLerpFactor, 0.f, 1.f);
        rotLerpFactor = glm::clamp(rotLerpFactor, 0.f, 1.f);

        currentTransform.position = glm::mix(currentTransform.position, targetTransform.position, posLerpFactor);
        currentTransform.pitch = glm::mix(currentTransform.pitch, targetTransform.pitch, rotLerpFactor);
        currentTransform.yaw = glm::mix(currentTransform.yaw, targetTransform.yaw, rotLerpFactor);
    }

    glm::mat4 CameraController::getViewMatrix() const {
        return glm::lookAt(currentTransform.position, currentTransform.position + getForward(), worldUp);
    }

    glm::vec3 CameraController::getPosition() const {
        return currentTransform.position;
    }

    glm::vec3 CameraController::getForward() const {
        float radPitch = glm::radians(currentTransform.pitch);
        float radYaw = glm::radians(currentTransform.yaw);

        glm::vec3 dir;
        dir.x = cos(radPitch) * cos(radYaw);
        dir.y = sin(radPitch);
        dir.z = cos(radPitch) * sin(radYaw);

        return glm::normalize(dir);
    }

    glm::vec3 CameraController::getRight() const {
        return glm::normalize(glm::cross(getForward(), worldUp));
    }

    glm::vec3 CameraController::getUp() const {
        return glm::normalize(glm::cross(getRight(), getForward()));
    }

    void CameraController::clampAngles() {
        targetTransform.pitch = std::clamp(targetTransform.pitch, -85.f, 85.f);
    }

}
#pragma once

#include "Camera.h"
#include "glm.hpp"

namespace Game {

    class CameraController {
    public:

        Engine::Camera::CameraTransform currentTransform;
        Engine::Camera::CameraTransform targetTransform;

        CameraController() {}

        void setTargetPosition(const glm::vec3& position);
        void setTargetPitch(float pitch);
        void setTargetYaw(float yaw);
        void addTargetPitch(float delta);
        void addTargetYaw(float delta);

        void setTransform(Engine::Camera::CameraTransform& transform);

        void init(Engine::Camera::CameraTransform transform);
        void update(float deltaTime);

        glm::mat4 getViewMatrix() const;
        glm::vec3 getPosition() const;
        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;

    private:

        static constexpr float positionSmoothness = 15.0f; // higher = snappier
        static constexpr float rotationSmoothness = 15.0f;
        static constexpr glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        void clampAngles();
    };
}
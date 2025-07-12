//#include "pch.h"
//#include "Camera.h"
//#include "CameraController.h"
//#include "AppSurface.h"
//#include "Core.h"
//#include "Input.h"

//#include "pch.h"

#include "OrbitCameraController.h"
#include "gtc/constants.hpp"

namespace Game{

    OrbitCameraController::OrbitCameraController()
        : m_target(0.0f, 0.0f, 0.0f),
        m_distance(3.0f),
        m_yaw(0.0f),
        m_pitch(0.0f),
        m_targetYaw(0.0f),
        m_targetPitch(0.0f),
        m_targetDistance(3.0f),
        m_yawVelocity(0.0f),
        m_pitchVelocity(0.0f),
        m_distanceVelocity(0.0f),
        m_position(0.0f, 0.0f, 3.0f),
        m_up(0.0f, 1.0f, 0.0f)
    {
    }

    void OrbitCameraController::Update(float deltaTime)
    {
        // Smooth damping
        auto smoothDamp = [](float current, float target, float& velocity, float smoothTime, float deltaTime) -> float {
            float omega = 2.0f / smoothTime;
            float x = omega * deltaTime;
            float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
            float change = current - target;
            float temp = (velocity + omega * change) * deltaTime;
            velocity = (velocity - omega * temp) * exp;
            return target + (change + temp) * exp;
        };

        m_yaw = smoothDamp(m_yaw, m_targetYaw, m_yawVelocity, smoothTime, deltaTime);
        m_pitch = smoothDamp(m_pitch, m_targetPitch, m_pitchVelocity, smoothTime, deltaTime);
        m_distance = smoothDamp(m_distance, m_targetDistance, m_distanceVelocity, smoothTime, deltaTime);

        // Clamp pitch
        const float pitchLimit = glm::radians(80.0f);
        m_pitch = glm::clamp(m_pitch, -pitchLimit, pitchLimit);

        // Calculate position
        float cosPitch = cosf(m_pitch);
        float sinPitch = sinf(m_pitch);
        float cosYaw = cosf(m_yaw);
        float sinYaw = sinf(m_yaw);

        glm::vec3 forward(
            cosPitch * cosYaw,
            sinPitch,
            cosPitch * sinYaw
        );

        m_position = m_target - forward * m_distance;
    }

    void OrbitCameraController::ProcessInput(float deltaYaw, float deltaPitch, float deltaZoom)
    {
        const float rotateSpeed = 1.5f; // radians per unit input
        const float zoomSpeed = 5.0f;   // units per unit input

        m_targetYaw += deltaYaw * rotateSpeed;
        m_targetPitch += deltaPitch * rotateSpeed;
        m_targetDistance += deltaZoom * zoomSpeed;

        m_targetDistance = glm::max(m_targetDistance, 1.0f);
    }

    glm::mat4 OrbitCameraController::GetViewMatrix() const
    {
        return glm::lookAt(m_position, m_target, m_up);
    }

    void OrbitCameraController::SetTarget(const glm::vec3& target)
    {
        m_target = target;
    }

    void OrbitCameraController::SetDistance(float distance)
    {
        m_distance = distance;
        m_targetDistance = distance;
    }

    void OrbitCameraController::SetYawPitch(float yaw, float pitch)
    {
        m_yaw = yaw;
        m_pitch = pitch;
        m_targetYaw = yaw;
        m_targetPitch = pitch;
    }


//    void CameraController::init(Engine::Camera::Camera& camera){
//
//        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, Engine::Core::getInstance()->appSurface.getAspectRatio(), 0.1f, 1000.0f);
//    }
//
//    void CameraController::update(Engine::Camera::Camera& camera, float dt){
//
//        Engine::Core* core = Engine::Core::getInstance();
//        Engine::Camera::perspectiveProjection(camera.projection, 90.0f, core->appSurface.getAspectRatio(), 0.1f, 1000.0f);
//
//#if PLATFORM == WIN
//        if(core->input.getButtonDown(Engine::InputCode::Mouse_Left)) {
//#endif
//            targetHorizontalAngle += -core->input.getPointerDelta().x * 0.01f;
//            horizontalAngle = glm::mix(horizontalAngle, targetHorizontalAngle, 0.1);
//
//            //core->input.set
//
//#if PLATFORM == WIN
//        }
//#endif
//
//        float radius = 5;
//        camera.position = glm::vec3(radius * glm::sin(horizontalAngle), 0, radius * glm::cos(horizontalAngle));
//        Engine::Camera::view(camera.view, camera.position, glm::vec3(0));
//    }

}
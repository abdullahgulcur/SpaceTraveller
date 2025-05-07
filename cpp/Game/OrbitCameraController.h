#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace Game {

    class OrbitCameraController
    {
    public:

        glm::vec3 m_up;
        glm::vec3 m_position;
        glm::vec3 m_target;

        OrbitCameraController();

        void Update(float deltaTime);
        void ProcessInput(float deltaYaw, float deltaPitch, float deltaZoom);

        glm::mat4 GetViewMatrix() const;

        void SetTarget(const glm::vec3& target);
        void SetDistance(float distance);
        void SetYawPitch(float yaw, float pitch);

    private:
        float m_distance;

        float m_yaw;      // radians
        float m_pitch;    // radians

        float m_targetYaw;
        float m_targetPitch;
        float m_targetDistance;

        float m_yawVelocity;
        float m_pitchVelocity;
        float m_distanceVelocity;


        const float smoothTime = 0.2f; // seconds to smooth toward target
    };
}

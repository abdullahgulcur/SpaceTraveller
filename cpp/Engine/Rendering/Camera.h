#pragma once

#include "glm.hpp"

namespace Engine{

    namespace Camera{

        struct CameraTransform {
            glm::vec3 position = glm::vec3(0.f);
            float pitch = 0.f;
            float yaw = -90.f;

            CameraTransform() {}
            CameraTransform(glm::vec3 position) : position(position) {}
            CameraTransform(glm::vec3 position, float pitch, float yaw) :
                position(position),
                pitch(pitch),
                yaw(yaw)
            {}
        };

        struct Camera{
            glm::mat4 view;
            glm::mat4 inverseView;
            glm::mat4 projection;
            glm::mat4 projectionView;
            glm::vec3 position;
            glm::vec3 right;
            glm::vec3 up;
            float fovY;
            float aspect;
            float zNear;
            float zFar;
        };

        void init(Camera& camera, float fovY, float aspect, float zNear = 0.1f, float zFar = 100000.f);
        void perspectiveProjection(Camera& camera);
        void lookAt(Camera& camera, glm::vec3 center, glm::vec3 up); // = glm::vec3(0.f, 1.f, 0.f)
        void lookAt(Camera& camera, glm::vec3 cameraPosition, glm::vec3 center, glm::vec3 up); //  = glm::vec3(0.f,1.f,0.f)
        void setView(Camera& camera, glm::mat4& view);
        void setFovY(Camera& camera, float fovY);
        void setAspect(Camera& camera, float aspect);
        void setZNear(Camera& camera, float zNear);
        void setZFar(Camera& camera, float zFar);
        void getCameraRightAndUp(Camera& camera);
        /*void perspectiveProjection(glm::mat4& projection, float fovY, float aspect, float zNear, float zFar);
        void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center, glm::vec3 up = glm::vec3(0.f, 1.f, 0.f));
        void getCameraRightAndUp(glm::mat4& view, glm::vec3& camRight, glm::vec3& camUp);*/

        void getView(CameraTransform transform, glm::mat4& view);
        void computePitchYawFromTarget(const glm::vec3& cameraPosition, const glm::vec3& targetPosition, float& outPitch, float& outYaw);


    }
}
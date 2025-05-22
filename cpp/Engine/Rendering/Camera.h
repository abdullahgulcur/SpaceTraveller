#pragma once

#include "glm.hpp"

namespace Engine{

    namespace Camera{

        struct Camera{
            glm::mat4 view;
            glm::mat4 projection;
            glm::vec3 position;
        };

        void perspectiveProjection(glm::mat4& projection, float fovY, float aspect, float zNear, float zFar);
        void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center);
        void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center, glm::vec3 up);
        void getCameraRightAndUp(glm::mat4& view, glm::vec3& camRight, glm::vec3& camUp);
    }
}
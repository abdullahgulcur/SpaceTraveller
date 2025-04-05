#pragma once

#include "glm.hpp"

namespace Engine{

    class PerspectiveCamera {

    private:
    public:

        PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane);
        ~PerspectiveCamera();
        glm::mat4 getProjectionMatrix();

    };
}
#pragma once

#include "glm.hpp"
#include "ext/matrix_clip_space.hpp"
#include "gtc/matrix_transform.hpp"

namespace Engine{

    namespace Camera{

        void perspectiveProjection(glm::mat4& projection, float fovY, float aspect, float zNear, float zFar){
            projection = glm::perspective(glm::radians(fovY), aspect, zNear, zFar);
        }

        void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center){
            view = glm::lookAt(camPos, center, glm::vec3(0,1,0));
        }

        void view(glm::mat4& view, glm::vec3& camPos, glm::vec3 center, glm::vec3 up){
            view = glm::lookAt(camPos, center, up);
        }



    }
}
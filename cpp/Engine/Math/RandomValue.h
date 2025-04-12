#pragma once

#include "glm.hpp"

namespace Engine{

    namespace Random{

        float randomFloat(float min, float max);
        glm::vec2 randomVec2(glm::vec2 min, glm::vec2 max);
        glm::vec3 randomVec3(glm::vec3 min, glm::vec3 max);

    }
}
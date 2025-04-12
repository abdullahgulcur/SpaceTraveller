#include "pch.h"
#include "RandomValue.h"

namespace Engine{

    namespace Random{

        float randomFloat(float min, float max){
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_real_distribution<float> distX(min, max);

            return distX(gen);
        }

        glm::vec2 randomVec2(glm::vec2 min, glm::vec2 max){
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_real_distribution<float> distX(min.x, max.x);
            std::uniform_real_distribution<float> distY(min.y, max.y);

            return glm::vec2(distX(gen), distY(gen));
        }

        glm::vec3 randomVec3(glm::vec3 min, glm::vec3 max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_real_distribution<float> distX(min.x, max.x);
            std::uniform_real_distribution<float> distY(min.y, max.y);
            std::uniform_real_distribution<float> distZ(min.z, max.z);

            return glm::vec3(distX(gen), distY(gen), distZ(gen));
        }

    }
}
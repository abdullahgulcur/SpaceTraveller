#include "pch.h"
#include "RandomValue.h"
#include "gtc/constants.hpp"
#include "gtc/random.hpp"

namespace Engine{

    namespace Random{

        float randomFloat(float min, float max){
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_real_distribution<float> distX(min, max);

            return distX(gen);
        }

        int random(int min, int max) {
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_int_distribution<int> distX(min, max);

            return static_cast<int>(distX(gen));
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

        glm::vec3 randomPointInSphereShell(float innerRadius, float outerRadius) {
            // 1. Get random direction on unit sphere
            glm::vec3 dir = glm::sphericalRand(1.0f);  // Already normalized

            // 2. Get random distance between inner and outer radius
            float dist = std::cbrt(randomFloat(std::pow(innerRadius, 3.0f), std::pow(outerRadius, 3.0f)));

            // 3. Scale direction
            return dir * dist;
        }

        glm::vec3 randomPointInCircleShell(float innerRadius, float outerRadius) {
            // 1. Get random direction on unit sphere
            glm::vec2 dir = glm::circularRand(1.0f);  // Already normalized

            // 2. Get random distance between inner and outer radius
            float dist = std::cbrt(randomFloat(std::pow(innerRadius, 3.0f), std::pow(outerRadius, 3.0f)));

            // 3. Scale direction
            return glm::vec3(dir.x * dist, 0.f, dir.y * dist);

        }

    }
}
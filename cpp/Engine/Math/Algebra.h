#pragma once

#include "glm.hpp"

namespace Engine{

    namespace Algebra{

        //template<typename T>
        //T linstep(T x, T a, T b, T c, T d){
        //    T value = (x - a) * (d - c) / (b - a) + c;
        //    return glm::clamp(value, glm::min(c,d), glm::max(c,d));
        //}

        float parametricSmooth(float x, float a) {
            if (x < 0.5) {
                x = x * 2.f;
                x = glm::pow(x, a) * 0.5f;
            }
            else {
                x = -(x * 2.f) + 2.f;
                x = glm::pow(x, a) * 0.5f;
                x = 1.f - x;
            }
            return x;
        }

    }
}
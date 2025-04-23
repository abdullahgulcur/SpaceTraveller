#pragma once

#include "glm.hpp"

namespace Engine{

    namespace Algebra{

        template<typename T>
        T linstep(T x, T a, T b, T c, T d){
            T value = (x - a) * (d - c) / (b - a) + c;
            return glm::clamp(value, glm::min(c,d), glm::max(c,d));
        }

    }
}
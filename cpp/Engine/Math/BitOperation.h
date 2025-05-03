#pragma once

#include "glm.hpp"

namespace Engine {

    namespace BitOperation {

        inline void setBit(unsigned int& num, int pos) {
            num |= (1U << pos);
        }

        // Get the bit at position 'pos'
        inline bool getBit(unsigned int num, int pos) {
            return (num >> pos) & 1U;
        }

        // Clear (reset) the bit at position 'pos'
        inline void clearBit(unsigned int& num, int pos) {
            num &= ~(1U << pos);
        }

        // Toggle (flip) the bit at position 'pos'
        inline void toggleBit(unsigned int& num, int pos) {
            num ^= (1U << pos);
        }

    }
}
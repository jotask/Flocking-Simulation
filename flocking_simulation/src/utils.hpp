#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

# define PI           3.14159265358979323846
# define PIf          3.14159265358979323846f

namespace aiko
{

    namespace utils
    {

        static float getRandom(const float min = 0.0f, const float max = 1.0f)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<float> dist(min, max);
            return dist(mt);
        }

        static glm::vec3 getRandomVector()
        {
            const auto x = getRandom(-1.0f, 1.0f);
            const auto y = getRandom(-1.0f, 1.0f);
            const auto z = getRandom(-1.0f, 1.0f);
            return { x, y, z };
        }

        static constexpr float radToDeg(const float radians)
        {
            return radians * static_cast<float>(180.0 / 3.141592653589793238463);
        }

    }

}
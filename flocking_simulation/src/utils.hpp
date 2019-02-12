#pragma once

#include <glm.hpp>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

namespace aiko
{

    namespace utils
    {

        template<class T>
        static T getRandom(const T min, const T max)
        {
            return min + (static_cast<int>(getRandom<T>()) % static_cast<int>(max - min + 1));
        }

        template<class T>
        static T getRandom()
        {
            // Seed with a real random value, if available
            std::random_device r;

            // Choose a random mean between 1 and 6
            std::default_random_engine e1(r());
            std::uniform_int_distribution<int> uniform_dist(1, 6);
            const auto mean = uniform_dist(e1);

            // Generate a normal distribution around that mean
            std::seed_seq seed2{ r(), r(), r(), r(), r(), r(), r(), r() };
            std::mt19937 e2(seed2);
            std::normal_distribution<> normal_dist(mean, 2);

            return static_cast<T>(normal_dist(e2));

        }

        static glm::vec3 getRandomVector()
        {
            const auto x = getRandom(0.0f, 1.0f);
            const auto y = getRandom(0.0f, 1.0f);
            const auto z = getRandom(0.0f, 1.0f);
            return { x, y, z };
        }

        static constexpr float radToDeg(const float radians)
        {
            return radians * static_cast<float>(180.0 / 3.141592653589793238463);
        }

    }

}
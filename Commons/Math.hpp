//
// Created by hw21a105 on 2023/12/20.
//

#ifndef OPE2023_MATH_HPP
#define OPE2023_MATH_HPP

#include <random>

namespace Math {
    const float Pi = 3.1415926535f;

    inline float Deg2Rad() {
        return Pi / 180.0f;
    }

    inline float Rad2Deg() {
        return 180.0f / Pi;
    }

    static std::random_device seed_gen;
    static std::default_random_engine randomEngine(seed_gen());

    inline float GetRand(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(Math::randomEngine);
    }

    inline int GetRand(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(Math::randomEngine);
    }
}

#endif //OPE2023_MATH_HPP
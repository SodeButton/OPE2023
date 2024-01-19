//
// Created by hw21a105 on 2024/01/19.
//

#ifndef OPE2023_UTILITY_HPP
#define OPE2023_UTILITY_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <SDL2/SDL_ttf.h>

namespace Utility {
    inline std::string FloatToString(float value, int precision = 2) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << value;
        return oss.str();
    }
}

#endif //OPE2023_UTILITY_HPP

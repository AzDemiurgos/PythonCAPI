#pragma once

#include <vector>


#ifdef ONGPU_EXPORTS
#define ONGPU_API __declspec(dllexport)
#else
#define ONGPU_API __declspec(dllimport)
#endif

#define matrix std::vector<std::vector<float>>

namespace onGPU
{
    ONGPU_API void calculate(matrix& data);
    //void innerCalculator(std::vector<std::vector<float>>& data);
}

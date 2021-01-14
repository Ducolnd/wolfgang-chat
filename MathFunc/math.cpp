#include <cmath>
#include "math.hpp"

namespace ducoMath {
    float sqrt(float num)
{
    if (num <= 0)
    {
        return 0;
    }
    return std::pow(num, 0.5);
}
}

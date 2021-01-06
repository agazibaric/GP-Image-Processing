#ifndef CARTESIAN_UTILITY_H
#define CARTESIAN_UTILITY_H
#include <vector>
namespace utility{
    using uint = unsigned int;
    uint vectorArgmax(const std::vector<double>& v);
    std::vector<std::vector<int>> initializeEmptyConfusionMatrix(const std::vector<int>& classes);
}
#endif //CARTESIAN_UTILITY_H

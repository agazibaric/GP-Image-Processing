#include <set>
#include "utility.h"
namespace utility{
    uint vectorArgmax(const std::vector<double>& v) {
        uint argmax = 0;
        double currentBest = v[0];
        for(uint i = 1; i < v.size(); i++) {
            if(v[i] > currentBest) {
                currentBest = v[i];
                argmax = i;
            }
        }
        return argmax;
    }

    std::vector<std::vector<int>> initializeEmptyConfusionMatrix(const std::vector<int>& classes) {
        std::set<int> diffClasses;
        for(const auto& elem : classes) {
            diffClasses.insert(elem);
        }
        std::vector<int> row(diffClasses.size(),0);
        return std::vector<std::vector<int>>(diffClasses.size(),row);
    }
}
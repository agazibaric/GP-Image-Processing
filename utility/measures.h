#ifndef UTILITY_MEASURES_H
#define UTILITY_MEASURES_H
#include <vector>
#include <string>
namespace utility
{
    using uint = unsigned int;

    double accuracy(int TP, int TN, int FP, int FN, int numberOfClasses, int alpha = 1);

    double error(int TP, int TN, int FP, int FN, int numberOfClasses, int alpha = 1);

    double precision(int TP, int FP, int numberOfClasses, int alpha = 1);

    double sensitivity(int TP, int FN, int numberOfClasses, int alpha = 1);

    double fallout(int FP, int TN, int numberOfClasses, int alpha = 1);

    double specificity(int TN, int FP, int numberOfClasses, int alpha = 1);

    double F1(int TP, int FP, int FN, int numberOfClasses, int alpha = 1);

    double FBeta(int TP, int FP, int FN, double beta, int numberOfClasses, int alpha = 1);

    double returnConfusionMatrixResult(const std::vector<std::vector<uint>>& confusionMatrix, uint size,
                                       const std::string& measureUsed, int alpha = 1);

    double meanSquareError(const std::vector<double>& trueOutput, const std::vector<double>& calculatedOutput);

    double rootMeanSquareError(const std::vector<double>& trueOutput, const std::vector<double>& calculatedOutput);
}
#endif //UTILITY_MEASURES_H

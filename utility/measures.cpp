#include "measures.h"
#include <vector>
#include <iostream>
#include <cmath>

namespace utility
{
    double accuracy(int TP, int TN, int FP, int FN, int numberOfClasses, int alpha)
    {
        double numerator = TP + TN + alpha;
        double nominator = TP + TN + FP + FN + numberOfClasses;
        return numerator/nominator;
    }

    double error(int TP, int TN, int FP, int FN, int numberOfClasses, int alpha)
    {
        double numerator = FP + FN + alpha;
        double nominator = TP + TN + FP + FN + numberOfClasses;
        return numerator/nominator;

    }

    double precision(int TP, int FP, int numberOfClasses, int alpha)
    {
        return (static_cast<double>(TP) + alpha) / (TP + FP + numberOfClasses);
    }

    double sensitivity(int TP, int FN, int numberOfClasses, int alpha)
    {
        return (static_cast<double>(TP) + alpha) / (TP + FN + numberOfClasses);
    }

    double fallout(int FP, int TN, int numberOfClasses, int alpha)
    {
        return (static_cast<double>(FP) + alpha) / (FP + TN + numberOfClasses);
    }

    double specificity(int TN, int FP, int numberOfClasses, int alpha)
    {
        return (static_cast<double>(TN) + alpha)/ (TN + FP + numberOfClasses);
    }

    double F1(int TP, int FP, int FN, int numberOfClasses, int alpha)
    {
        double P = precision(TP,FP,numberOfClasses,alpha);
        double R = sensitivity(TP,FN,numberOfClasses,alpha);
        return (2 * P * R) / (P + R);
    }

    double FBeta(int TP, int FP, int FN, double beta, int numberOfClasses, int alpha)
    {
        double P = precision(TP,FP,numberOfClasses,alpha);
        double R = sensitivity(TP,FN,numberOfClasses,alpha);
        return ((1 + beta * beta) * P * R) / (beta * beta * P + R);
    }
    double returnConfusionMatrixResult(const std::vector<std::vector<uint>>& confusionMatrix, uint size,
                                       const std::string& measureUsed, int alpha)
    {
        std::vector<double> calculatedMeasures;
        uint numberOfClasses = confusionMatrix.size();
        uint TP=0,TN=0,FP=0,FN=0;
        for(uint i = 0; i < numberOfClasses; i++) {
            TP += confusionMatrix[i][i];
            for(uint j = 0; j < confusionMatrix[i].size(); j++) {
                if(i != j) {
                    FP += confusionMatrix[i][j];
                }
            }
            for(uint j = 0; j < confusionMatrix.size(); j++) {
                if(i != j) {
                    FN += confusionMatrix[j][i];
                }
            }
            TN = size - TP - FP - FN;
            if(measureUsed == "f1" || measureUsed == "f1score" ) {
                calculatedMeasures.push_back(F1(TP,FP,FN,numberOfClasses,alpha));
            }
            else if(measureUsed == "precision") {
                calculatedMeasures.push_back(precision(TP,FP,numberOfClasses, alpha));
            }
            else if(measureUsed == "specificity") {
                calculatedMeasures.push_back(specificity(TN,FP,numberOfClasses,alpha));
            }
            else if(measureUsed == "sensitivity" || measureUsed == "recall" || measureUsed == "true positive rate") {
                calculatedMeasures.push_back(sensitivity(TP,FN,numberOfClasses,alpha));
            }
            else if(measureUsed == "fallout" || measureUsed == "false positive rate") {
                calculatedMeasures.emplace_back(fallout(FP,TN,numberOfClasses,alpha));
            }
            else if(measureUsed == "error") {
                calculatedMeasures.push_back(error(TP,TN,FP,FN,numberOfClasses,alpha));
            }
            else {
                calculatedMeasures.push_back(accuracy(TP,TN,FP,FN,numberOfClasses,alpha));
            }
        }
        double measure = 0.0;
        for(const auto& elem : calculatedMeasures) {
            measure += elem;
        }
        return measure / calculatedMeasures.size();
    }

    double meanSquareError(const std::vector<double>& trueOutput, const std::vector<double>& calculatedOutput)
    {
        double sum = 0.0;
        if(trueOutput.size() != calculatedOutput.size()) {
            std::cerr << "Mean square error encountered an error.  Calculated output and true output are not of same size.\n";
        }
        for(uint i = 0; i < trueOutput.size(); i++) {
            sum += (trueOutput[i] - calculatedOutput[i]) * (trueOutput[i] - calculatedOutput[i]);
        }
        return sum / trueOutput.size();
    }

    double rootMeanSquareError(const std::vector<double>& trueOutput, const std::vector<double>& calculatedOutput)
    {
        double sum = 0.0;
        if(trueOutput.size() != calculatedOutput.size()) {
            std::cerr << "Root mean square error encountered an error. Calculated output and true output are not of same size.\n";
        }
        for(uint i = 0; i < trueOutput.size(); i++) {
            sum += (trueOutput[i] - calculatedOutput[i]) * (trueOutput[i] - calculatedOutput[i]);
        }
        return std::sqrt(sum / trueOutput.size());
    }
}
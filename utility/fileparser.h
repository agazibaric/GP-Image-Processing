#ifndef CARTESIAN_CSVPARSER_H
#define CARTESIAN_CSVPARSER_H
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include "ecf/ECF_base.h"

namespace utility{
    using PairAllFeaturesAllLabels = std::pair<std::vector<std::vector<double>>,std::vector<uint>>;
    /**
     *
     * @param file_name
     * @return Vector of strings where each string represents a line from <i>file_name</i>
     */
    std::vector<std::string> parseCSVFromFile(const std::string& file_name);

    /**
     *
     * @param csv - result of parseCSVFromFile
     * @param leadsWithID - If set to true, first number will be ignored.
     * @return std::vector<std::vector<double>> -> For each example from dataset file, std::vector<double> is created.
     *                                             That vector holds values of features for that example.
     *         std::vector<int>                 -> Each int in vector represents class of that example in dataset.
     */
    PairAllFeaturesAllLabels parseStringIntoFeaturesAndLabels(const std::vector<std::string>& csv, bool leadsWithID = false);

    /**
     *
     * @param line - which is split into function arguments and values (i.e. 13 14 15 -> x=13, y=14, f(x,y) = 15)
     * @return  std::pair<std::vector<double>,double>  -> std::vector<double> - values for function arguments
     *                                                 -> double - value of a function.
     */
    std::pair<std::vector<double>,double> parseArgumentsAndFunctionValues(const std::string& line);

}
#endif //CARTESIAN_CSVPARSER_H

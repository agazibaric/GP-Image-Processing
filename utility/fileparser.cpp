#include <iostream>
#include <boost/algorithm/string.hpp>
#include <set>
#include <map>
#include "fileparser.h"

namespace utility{
    std::vector<std::string> parseCSVFromFile(const std::string& file_name)
    {
        std::vector<std::string> parsed;
        std::ifstream in_file(file_name);
        if(!in_file) {
            std::cerr << "Parser could not load a .csv file named: " << file_name << '\n';
            exit(-1);
        }
        for(std::string line; getline(in_file,line);) {
            parsed.emplace_back(std::move(line));
        }
        in_file.close();
        return parsed;
    }


    PairAllFeaturesAllLabels parseStringIntoFeaturesAndLabels(const std::vector<std::string>& csv, bool leadsWithID)
    {
        std::vector<std::vector<double>> allFeatures;
        std::vector<uint> allLabels;
        std::set<int> distinct;
        std::map<std::string,int> keyLabelMap;
        uint generalClassLabel = 0;
        for(const auto& line : csv) {
            std::vector<std::string> splitsContainer;
            boost::split(splitsContainer, line, boost::is_any_of(","));
            std::vector<double> features;
            for(uint i = leadsWithID ? 1 : 0; i < splitsContainer.size() - 1; i++) {
                features.emplace_back(std::stod(splitsContainer[i]));
            }
            allFeatures.push_back(std::move(features));
            std::string last = splitsContainer[splitsContainer.size() - 1];
            if(keyLabelMap.find(last) == keyLabelMap.end()) {
                keyLabelMap.insert(std::make_pair(last,generalClassLabel));
                allLabels.push_back(generalClassLabel);
                distinct.insert(generalClassLabel);
                generalClassLabel++;
            }
            else {
                allLabels.push_back(keyLabelMap[last]);
            }
        }
        return std::make_pair(allFeatures,allLabels);
    }

    std::pair<std::vector<double>,double> parseArgumentsAndFunctionValues(const std::string& line)
    {
        std::vector<std::string> splitsContainer;
        boost::split(splitsContainer,line,boost::algorithm::is_space());
        std::vector<double> arguments;
        double functionValue;
        for(uint i = 0; i < splitsContainer.size() - 1; i++) {
            try{
                arguments.push_back(std::stod(splitsContainer[i]));
            }catch(std::exception& ex) {
                std::cerr << "An error occurred while converting a string into a double: " << splitsContainer[i] << '\n';
            }
        }
        try{
            functionValue = std::stod(splitsContainer[splitsContainer.size() - 1]);
        }catch(std::exception& ex) {
            std::cerr << "An error occured while converting a string into a double: " << splitsContainer[splitsContainer.size() - 1] << '\n';
        }
//        for(uint i = 0; i < arguments.size(); i++) {
//            std::cout << i << " " << arguments[i] << '\n';
//        }
        return std::make_pair(arguments,functionValue);
    }
}
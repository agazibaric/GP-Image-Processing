#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/algorithm/string.hpp>

using namespace std;

class IP
{
public:
    static constexpr int IMG_WIDTH = 512;
    static constexpr int IMG_HEIGHT = 512;

    static constexpr double MIN_VALUE = 0;
    static constexpr double MAX_VALUE = 255;

    static void convolution(vector<double> image, vector<double>& generatedImage, 
        int width, int height, cartesian::Cartesian* cartesian, int convolutionSize, double percentage, double offset_perc) {
        int delta = convolutionSize / 2;;
        int imageSize = (int)(image.size() * percentage);
        int imageOffset = (int)(image.size() * offset_perc);

        int N = imageOffset + imageSize;
        if (N > image.size()) {
            N = image.size();
        }

        for (int j = imageOffset; j < N; j++) {
            int pixelRow = j / IP::IMG_WIDTH;
            int pixelCol = j % IP::IMG_HEIGHT;
            vector<double> convolutionInputs;
            for (int convRow = pixelRow - delta; convRow <= pixelRow + delta; convRow++) {
                for (int convCol = pixelCol - delta; convCol <= pixelCol + delta; convCol++) {
                    if (convRow == pixelRow && convCol == pixelCol)
                        continue; // Skip pixel that we are trying to reconstruct
                    if (convRow < 0 || convRow >= width ||
                        convCol < 0 || convCol >= height) {
                        // We are off the image
                        convolutionInputs.push_back(0);
                    }
                    else {
                        // Find the correct pixel index
                        int pixelIndex = convRow * IP::IMG_WIDTH + convCol;
                        convolutionInputs.push_back(image[pixelIndex]);
                    }
                }
            }

            vector<double> result;
            cartesian->evaluate(convolutionInputs, result);
            generatedImage.push_back(result[0]);
        }
    }

    static void fixInvalidValues(vector<double>& v) {
        for (int i = 0, n = v.size(); i < n; i++) {
            /*v[i] = min(v[i], IP::MAX_VALUE);
            v[i] = max(v[i], IP::MIN_VALUE);*/
            v[i] = min(v[i], 255.);
            v[i] = max(v[i], 0.);
        }
    }

    static double euclideanNorm(vector<double> v) {
        double result = 0;
        for (double value : v) {
            result += value * value;
        }
        return result;
    }

    static double absoluteSum(vector<double> v) {
        double result = 0;
        for (double value : v) {
            result += std::abs(value);
        }
        return result;
    }

    static void scale(vector<double>& v, double scl) {
        for (int i = 0, n = v.size(); i < n; i++) {
            v[i] *= scl;
        }
    }

    static vector<double> loadImageFromVector(const char* fileName) {
        vector<double> image;
        ifstream inputFile(fileName);
        // test file open   
        double value;
        while (inputFile >> value) {
            image.push_back(value);
        }
        inputFile.close();
        return image;
    }

    static void writeToFile(const char* fileName, vector<double> v) {
        ofstream file;
        file.open(fileName);
        for (double value : v) {
            file << value << " ";
        }
        file << "\n";
        file.close();
    }


    static std::vector<std::string> split(const std::string& s) {
        std::vector<std::string> strs;
        boost::split(strs, s, boost::is_any_of(" "));
        return strs;
    }

};

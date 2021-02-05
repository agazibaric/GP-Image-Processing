#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/algorithm/string.hpp>

using namespace std;

/**
 * Image Processing
 */
class IP
{
public:
    static void convolution(vector<double> image, vector<double>& generatedImage, 
        int width, int height, cartesian::Cartesian* cartesian, int convolutionSize, double percentage, int includeCentralPixel) {
        int delta = convolutionSize / 2;
        int imageSize = (int)(image.size() * percentage);

        // Calculate row shift for given image size percentage
        int nRows = imageSize / width;
        int rowDelta = height / nRows;

        for (int row = 0; row < nRows; row++) {
            int pixelRow = row * rowDelta;
            int nCols = width;

            // If it's last row, calculate number of columns
            if (row == nRows - 1 && percentage < 1.) {
                nCols = imageSize - nRows * width;
            }

            // Convolution window
            for (int pixelCol = 0; pixelCol < nCols; pixelCol++) {
                vector<double> convolutionInputs;
                for (int convRow = pixelRow - delta; convRow <= pixelRow + delta; convRow++) {
                    for (int convCol = pixelCol - delta; convCol <= pixelCol + delta; convCol++) {
                        if (!includeCentralPixel && convRow == pixelRow && convCol == pixelCol)
                            continue; // Skip central pixel
                        if (convRow < 0 || convRow >= width ||
                            convCol < 0 || convCol >= height) {
                            // We are off the image, add padding with zeros
                            convolutionInputs.push_back(0);
                        }
                        else {
                            // Find the correct pixel index
                            int pixelIndex = convRow * width + convCol;
                            convolutionInputs.push_back(image[pixelIndex]);
                        }
                    }
                }

                vector<double> result;
                cartesian->evaluate(convolutionInputs, result);
                generatedImage.push_back(result[0]);
            }

        }
    }

    static void fixInvalidValues(vector<double>& v, double minValue, double maxValue) {
        for (int i = 0, n = v.size(); i < n; i++) {
            v[i] = min(v[i], maxValue);
            v[i] = max(v[i], minValue);
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

#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include "./utility/utilityrng.h"
#include "ConvolutionParams.h"

using namespace std;

/**
 * Image Processing
 */
class IP
{
public:

    static void convolution2(vector<double> image, vector<double>& generatedImage, 
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

    static void convolution(vector<double> image, vector<double>& generatedImage, cartesian::Cartesian* cartesian, ConvolutionParamsP params) {
        // Submatrix passage
        for (int pixelRow = params->rowStart, M = params->rowStart + params->nRows; pixelRow < M; pixelRow++) {            
            for (int pixelCol = params->colStart, N = params->colStart + params->nCols; pixelCol < N; pixelCol++) {
                vector<double> convolutionInputs;

                // Convolution window
                for (int convRow = pixelRow - params->delta, m = pixelRow + params->delta; convRow <= m; convRow++) {
                    for (int convCol = pixelCol - params->delta, n = pixelCol + params->delta; convCol <= n; convCol++) {
                        if (!params->includeCentralPixel && convRow == pixelRow && convCol == pixelCol)
                            continue; // Skip central pixel
                        if (convRow < 0 || convRow >= params->width ||
                            convCol < 0 || convCol >= params->height) {
                            // We are off the image, add padding with zeros
                            convolutionInputs.push_back(0);
                        }
                        else {
                            // Find the correct pixel index
                            int pixelIndex = convRow * params->width + convCol;
                            convolutionInputs.push_back(image[pixelIndex]);
                        }
                    }
                }

                vector<double> result;
                cartesian->evaluate(convolutionInputs, result);
                generatedImage.push_back(abs(result[0]));
            }

        }
    }

    static void getConvolutionInputs2(vector<double> image, vector<vector<double>>& convolutionInputs, ConvolutionParamsP params) {
        for (int j = 0; j < params->imageSize; j++) {
            int pixelRow = j / params->width;
            int pixelCol = j % params->height;
            vector<double> convolutionInput;
            for (int convRow = pixelRow - params->delta; convRow <= pixelRow + params->delta; convRow++) {
                for (int convCol = pixelCol - params->delta; convCol <= pixelCol + params->delta; convCol++) {
                    if (convRow == pixelRow && convCol == pixelCol)
                        continue; // Skip pixel that we are trying to reconstruct
                    if (convRow < 0 || convRow >= params->width ||
                        convCol < 0 || convCol >= params->height) {
                        // We are off the image
                        convolutionInput.push_back(0);
                    }
                    else {
                        // Find the correct pixel index
                        int pixelIndex = convRow * params->width + convCol;
                        convolutionInput.push_back(image[pixelIndex]);
                    }
                }
            }
            convolutionInputs.push_back(convolutionInput);
        }
    }

    static void getConvolutionInputs(vector<double> image, vector<vector<double>>& convolutionInputs, ConvolutionParamsP params) {
        // Submatrix passage
        for (int pixelRow = params->rowStart, M = params->rowStart + params->nRows; pixelRow < M; pixelRow++) {          
            for (int pixelCol = params->colStart, N = params->colStart + params->nCols; pixelCol < N; pixelCol++) {
                vector<double> convolutionInput;

                // Convolution window
                for (int convRow = pixelRow - params->delta, m = pixelRow + params->delta; convRow <= m; convRow++) {
                    for (int convCol = pixelCol - params->delta, n = pixelCol + params->delta; convCol <= n; convCol++) {
                        if (!params->includeCentralPixel && convRow == pixelRow && convCol == pixelCol)
                            continue; // Skip central pixel
                        if (convRow < 0 || convRow >= params->width ||
                            convCol < 0 || convCol >= params->height) {
                            // We are off the image, add padding with zeros
                            convolutionInput.push_back(0);
                        }
                        else {
                            // Find the correct pixel index
                            int pixelIndex = convRow * params->width + convCol;
                            convolutionInput.push_back(image[pixelIndex]);
                        }
                    }
                }

                convolutionInputs.push_back(convolutionInput);
            }

        }
    }

    static void getTagretImageConvolutionPixels(vector<double> image, vector<double>& result, ConvolutionParamsP params) {
        for (int pixelRow = params->rowStart, M = params->rowStart + params->nRows; pixelRow < M; pixelRow++) {          
            for (int pixelCol = params->colStart, N = params->colStart + params->nCols; pixelCol < N; pixelCol++) {
                int pixelIndex = pixelRow * params->width + pixelCol;
                result.push_back(image[pixelIndex]);
            }
        }
    }

    static void getTagretImageConvolutionPixels2(vector<double> image, vector<double>& result, ConvolutionParamsP params) {
        for (int i = 0; i < params->imageSize; i++) {
            result.push_back(image[i]);
        }
    }

    static void fixInvalidValues(vector<double>& v, double minValue, double maxValue) {
        for (int i = 0, n = v.size(); i < n; i++) {
            v[i] = round(v[i]);
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

    static double calculateError(vector<double> generatedImage, vector<double> targetImage, int power) {
        vector<double> difference;
        for (int pixel = 0, k = generatedImage.size(); pixel < k; pixel++) {
			difference.push_back(targetImage[pixel] - generatedImage[pixel]);
		}
        double result = 0;
        for (double value : difference) {
            result += pow(abs(value), power);
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

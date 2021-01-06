#pragma once
#include <torch/script.h>
#include <Net.h>

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include <boost/algorithm/string.hpp>

using namespace std;

class MNIST
{
public:
    static constexpr int IMG_WIDTH = 28;
    static constexpr int IMG_HEIGHT = 28;

    static constexpr double MEAN = 0.13707;
    static constexpr double STD = 0.3081;

    /*static constexpr double MIN_VALUE = (0 - MEAN) / STD;
    static constexpr double MAX_VALUE = (1 - MEAN) / STD;*/

    static constexpr double MIN_VALUE = 0;
    static constexpr double MAX_VALUE = 255;

    static vector<double> tensorToVector(torch::Tensor t) {
        vector<float> v(t.data_ptr<float>(), t.data_ptr<float>() + t.numel());
        vector<double> doubleVec(v.begin(), v.end());
        return doubleVec;
    }

    static torch::Tensor vectorToTensor(vector<double> v) {
        vector<float> floatVec(v.begin(), v.end());
        return torch::from_blob(floatVec.data(), { 1, 1, MNIST::IMG_WIDTH, MNIST::IMG_HEIGHT }).clone();
    }

    static torch::Tensor unNormalize(torch::Tensor tensor) {
        torch::data::transforms::Normalize<> n(-MNIST::MEAN / MNIST::STD, 1. / MNIST::STD);
        return n.operator()(tensor);
    }

    static torch::Tensor normalize(torch::Tensor tensor) {
        torch::data::transforms::Normalize<> n(MNIST::MEAN, MNIST::STD);
        return n.operator()(tensor);
    }

    static void convolution(vector<double> image, vector<double>& generatedImage, 
        int width, int height, cartesian::Cartesian* cartesian, int convolutionSize) {
        int delta = convolutionSize / 2;;
        for (int j = 0, imageSize = image.size(); j < imageSize; j++) {
            // 3 x 3 convolution
            int pixelRow = j / 28;
            int pixelCol = j % 28;
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
                        int pixelIndex = convRow * MNIST::IMG_WIDTH + convCol;
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
            v[i] = min(v[i], MNIST::MAX_VALUE);
            v[i] = max(v[i], MNIST::MIN_VALUE);
        }
    }

    static vector<double> combine(vector<double> a, vector<double> b) {
        assert(a.size() == b.size());

        std::vector<double> result;
        result.reserve(a.size());

        // Sum two vectors by elements
        auto transformFunction = std::plus<double>();
        std::transform(a.begin(), a.end(), b.begin(),
            std::back_inserter(result), transformFunction);

        return result;
    }

    static double euclideanNorm(vector<double> v) {
        //double result = sqrt(inner_product(begin(v), end(v), begin(v), 0));
        double result = 0;
        for (double value : v) {
            result += value * value;
        }
        return result;
    }

    static double absoluteSum(vector<double> v) {
        //double result = sqrt(inner_product(begin(v), end(v), begin(v), 0));
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

    static shared_ptr<Net> loadModel(const char* model_path) {
        auto model = make_shared<Net>();
        try {
            torch::load(model, model_path);
            cout << "Model loaded.\n";
        }
        catch (const c10::Error& e) {
            cerr << "Error while loading the model.\n";
            throw e;
        }
        return model;
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

    static vector<std::vector<double>> loadTargetData(int target) {
        // Create multi-threaded data loader for MNIST data
        auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            move(torch::data::datasets::MNIST("./data/mnist")
                //.map(torch::data::transforms::Normalize<>(MNIST::MEAN, MNIST::STD))
                .map(torch::data::transforms::Stack<>())), 1);

        vector<vector<double>> filtered;
        int trainingDataSize = 1;
        int count = 0;
        for (auto& batch : *data_loader) {
            int batchTarget = batch.target[0].item<int>();
            if (batchTarget == target) {
                count++;
                filtered.push_back(MNIST::tensorToVector(batch.data));
            }
            
            if (count >= trainingDataSize) {
                break;
            } 
        }
        return filtered;
    }

    static double calcAccuracy(vector<vector<double>> testData, cartesian::Cartesian* bestModel, shared_ptr<Net> targetModel, int targetValue) {
        int count = 0;
        for (vector<double> originalImg : testData) {
            vector<double> filter;
            bestModel->evaluate(originalImg, filter);
            vector<double> adversarialImage = MNIST::combine(originalImg, filter);
            MNIST::fixInvalidValues(adversarialImage);
            torch::Tensor tensorAdversarialImg = MNIST::vectorToTensor(adversarialImage);
            auto prediction = targetModel->forward(tensorAdversarialImg);
            int predictionValue = prediction.argmax().view({ 1 })[0].item<int>();
            if (predictionValue == targetValue) {
                count++;
            }
        }
        return (1. * count) / testData.size();
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

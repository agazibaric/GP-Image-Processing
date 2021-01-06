#include <ecf/ECF.h>
#include "cartesian/Cartesian.h"
#include "AdversarialOp.h"
#include <iostream>

#include <algorithm>
#include <functional>
#include <Mnist.h>

void writeInfo(const char* fileName, vector<vector<double>> testData, StateP state, shared_ptr<Net> targetModel, int targetValue) {
    ofstream file;
    file.open(fileName);

    vector<IndividualP> best = state->getHoF()->getBest();
    cartesian::Cartesian* bestModel = (cartesian::Cartesian*) best[0]->getGenotype().get();
    vector<double> stats = state->getStats()->getStats(-1);

    double accuracy = MNIST::calcAccuracy(testData, bestModel, targetModel, targetValue);
    double minFitness = stats[0];
    double maxFitness = stats[1];
    double average = stats[2];
    double stdDev = stats[3];
    int sampleSize = (int)stats[4];
    double time = stats[5];
    int evaluations = (int)stats[6];
    int generations = state->getGenerationNo();
    double lowest = stats[7];
    double highest = stats[8];

    file << "accuracy: " << accuracy << endl;
    file << "minFitness: " << minFitness << endl;
    file << "maxFitness: " << maxFitness << endl;
    file << "average: " << average << endl;
    file << "stdDev: " << stdDev << endl;
    file << "sampleSize: " << sampleSize << endl;
    file << "time: " << time << endl;
    file << "evaluations: " << evaluations << endl;
    file << "generations: " << evaluations << endl;
    file << "lowest: " << lowest << endl;
    file << "highest: " << highest << endl;

    //free(bestModel);
    file.close();
}

int main(int argc, char** argv) {
    StateP state(new State);
    CartesianP cgp(new cartesian::Cartesian);
    state->addGenotype(cgp);

    AdversarialOpP adversarialOp(new AdversarialOp());
    state->setEvalOp(adversarialOp);
    state->initialize(argc, argv);
    state->run();

    vector<IndividualP> best = state->getHoF()->getBest();
    cartesian::Cartesian* bestModel = (cartesian::Cartesian*) best[0]->getGenotype().get();

    MNIST::writeToFile("Noised.txt", adversarialOp->training_data[0]);

    vector<double> image = adversarialOp->training_data[0];
    vector<double> generatedImage;
    MNIST::convolution(image, generatedImage, MNIST::IMG_WIDTH, MNIST::IMG_HEIGHT, bestModel, 5);
    MNIST::fixInvalidValues(generatedImage);
    MNIST::writeToFile("Denoised.txt", generatedImage);
    
    //auto testData = MNIST::loadTargetData(5);
    //auto targetModel = adversarialOp->targetModel;
    //
    //auto originalImg = testData[1];
    //vector<double> filter;
    //bestModel->evaluate(originalImg, filter);
    //vector<double> adversarialImage = MNIST::combine(originalImg, filter);
    //MNIST::fixInvalidValues(adversarialImage);
    //torch::Tensor tensorAdversarialImg = MNIST::vectorToTensor(adversarialImage);
    //torch::Tensor normTensorAdversarialImg = MNIST::unNormalize(tensorAdversarialImg);

    //// Write adversarial img to file
    //MNIST::writeToFile("advImg10.txt", MNIST::tensorToVector(normTensorAdversarialImg));

    //// Write detailed info to file
    //int targetValue = 6;
    //writeInfo("info1.txt", testData, state, targetModel, targetValue);

    return 0;
}

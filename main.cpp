#include <ECF/ECF.h>
#include "cartesian/Cartesian.h"
#include "ImageProcessingOp.h"
#include <iostream>

#include <algorithm>
#include <functional>
#include "IP.h"

void writeInfo(const char* fileName, StateP state) {
    ofstream file;
    file.open(fileName);

    vector<IndividualP> best = state->getHoF()->getBest();
    cartesian::Cartesian* bestModel = (cartesian::Cartesian*) best[0]->getGenotype().get();
    vector<double> stats = state->getStats()->getStats(-1);

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

    file.close();
}

int main(int argc, char** argv) {
    StateP state(new State);
    CartesianP cgp(new cartesian::Cartesian);
    state->addGenotype(cgp);

    ImageProcessingOpP ipOp(new ImageProcessingOp());
    state->setEvalOp(ipOp);
    state->initialize(argc, argv);
    state->run();

    vector<IndividualP> best = state->getHoF()->getBest();
    cartesian::Cartesian* bestModel = (cartesian::Cartesian*) best[0]->getGenotype().get();

    IP::writeToFile("training-img.txt", ipOp->training_data[0]);

    vector<double> image = ipOp->training_data[0];
    vector<double> generatedImage;
    IP::convolution(image, generatedImage, IP::IMG_WIDTH, IP::IMG_HEIGHT, bestModel, 7, 1., 0.);
    IP::fixInvalidValues(generatedImage);
    IP::writeToFile("generated-img.txt", generatedImage);

    IP::writeToFile("goal-img.txt", ipOp->original_images[0]);

    writeInfo("results.txt", state);
    
    //auto testData = IP::loadTargetData(5);
    //auto targetModel = ImageProcessingOp->targetModel;
    //
    //auto originalImg = testData[1];
    //vector<double> filter;
    //bestModel->evaluate(originalImg, filter);
    //vector<double> adversarialImage = IP::combine(originalImg, filter);
    //IP::fixInvalidValues(adversarialImage);
    //torch::Tensor tensorAdversarialImg = IP::vectorToTensor(adversarialImage);
    //torch::Tensor normTensorAdversarialImg = IP::unNormalize(tensorAdversarialImg);

    //// Write adversarial img to file
    //IP::writeToFile("advImg10.txt", IP::tensorToVector(normTensorAdversarialImg));

    //// Write detailed info to file
    //int targetValue = 6;
    

    return 0;
}

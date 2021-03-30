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

    ipOp->params->percentage = 1.;
    ipOp->params->nRows = ipOp->params->height;
    ipOp->params->nCols = ipOp->params->width;
    ipOp->params->rowStart = 0;
    ipOp->params->colStart = 0;

    IP::writeToFile("conv-target.txt", ipOp->targetImagesConvolutionPixels[0]);
    IP::writeToFile("conv-training.txt", ipOp->convolutionInputsForImages[0][20]);

    // Training images
    for (int i = 0; i < ipOp->trainingImages.size(); i++) {
        vector<double> image = ipOp->trainingImages[i];
        vector<double> generatedImage;

        IP::convolution(image, generatedImage, bestModel, ipOp->params);
        IP::fixInvalidValues(generatedImage, ipOp->imageMinValue, ipOp->imageMaxValue);

        string trainingName = "training-img" + std::to_string(i) + ".txt";
        string generatedName = "generated-img" + std::to_string(i) + ".txt";
        string targetName = "target-img" + std::to_string(i) + ".txt";
        IP::writeToFile(trainingName.c_str(), ipOp->trainingImages[i]);
        IP::writeToFile(generatedName.c_str(), generatedImage);
        IP::writeToFile(targetName.c_str(), ipOp->targetImages[i]);
    }

    // Validation images
    for (int i = 0; i < ipOp->validationImages.size(); i++) {
        vector<double> image = ipOp->validationImages[i];
        vector<double> generatedImage;

        IP::convolution(image, generatedImage, bestModel, ipOp->params);
        IP::fixInvalidValues(generatedImage, ipOp->imageMinValue, ipOp->imageMaxValue);

        string validationName = "validation-img" + std::to_string(i) + ".txt";

        IP::writeToFile(validationName.c_str(), generatedImage);
    }

    writeInfo("results.txt", state);
    
    return 0;
}

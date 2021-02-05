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

    vector<double> image = ipOp->trainingImages[0];
    vector<double> generatedImage;
    IP::convolution(image, generatedImage, ipOp->imageWidth, ipOp->imageHeight, bestModel, ipOp->convolutionSize, 1., 0.);
    IP::fixInvalidValues(generatedImage, ipOp->imageMinValue, ipOp->imageMaxValue);

    IP::writeToFile("training-img.txt", ipOp->trainingImages[0]);
    IP::writeToFile("generated-img.txt", generatedImage);
    IP::writeToFile("target-img.txt", ipOp->targetImages[0]);

    writeInfo("results.txt", state);
    
    return 0;
}

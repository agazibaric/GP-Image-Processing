#pragma once
#include <ECF/ECF.h>
#include "cartesian/Cartesian.h"
#include "IP.h"
#include "./utility/utilityrng.h"

using namespace std;

class ImageProcessingOp : public EvaluateOp
{
public:
	ImageProcessingOp();
	void registerParameters(StateP state);
	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);

	vector<vector<double>> trainingImages;
	vector<vector<double>> targetImages;
	vector<vector<double>> validationImages;

	ConvolutionParamsP params;
	// Precalculated values for inputs
	vector<vector<vector<double>>> convolutionInputsForImages;
	// Precalculated target values
	vector<vector<double>> targetImagesConvolutionPixels;

	int imageWidth;
	int imageHeight;
	double imageMaxValue;
	double imageMinValue;
	int convolutionSize;
	double sizePercentage;
	int includeCentralPixel;
	double offsetPercentage = 0.;
};
typedef boost::shared_ptr<ImageProcessingOp> ImageProcessingOpP;

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
	
	int imageWidth;
	int imageHeight;
	double imageMaxValue;
	double imageMinValue;
	int convolutionSize;
	double sizePercentage;
	double offsetPercentage = 0.;
};
typedef boost::shared_ptr<ImageProcessingOp> ImageProcessingOpP;

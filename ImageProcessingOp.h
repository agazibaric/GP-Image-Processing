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
	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);

	vector<vector<double>> training_data;
	vector<vector<double>> original_images;
};
typedef boost::shared_ptr<ImageProcessingOp> ImageProcessingOpP;

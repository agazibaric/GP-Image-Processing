#pragma once
#include "ecf/ECF.h"
#include "cartesian/Cartesian.h"
#include <Mnist.h>
#include "./utility/utilityrng.h"

using namespace std;

class AdversarialOp : public EvaluateOp
{
public:
	AdversarialOp();
	FitnessP evaluate(IndividualP individual);
	bool initialize(StateP);

	shared_ptr<Net> targetModel;
	vector<vector<double>> training_data;
	vector<vector<double>> original_images;

	int target;
	int fakeTarget;
};
typedef boost::shared_ptr<AdversarialOp> AdversarialOpP;

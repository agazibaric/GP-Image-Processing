#include "ImageProcessingOp.h"

ImageProcessingOp::ImageProcessingOp() {}

void ImageProcessingOp::registerParameters(StateP state)
{
	state->getRegistry()->registerEntry("convolutionSize", (voidP)(new int(3)), ECF::INT);
	state->getRegistry()->registerEntry("sizePercentage", (voidP)(new double(0.01)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("imageWidth", (voidP)(new int(512)), ECF::INT);
	state->getRegistry()->registerEntry("imageHeight", (voidP)(new int(512)), ECF::INT);
	state->getRegistry()->registerEntry("imageMaxValue", (voidP)(new double(255)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("imageMinValue", (voidP)(new double(0)), ECF::DOUBLE);
	state->getRegistry()->registerEntry("targetImgPath", (voidP)(new string("")), ECF::STRING);
	state->getRegistry()->registerEntry("trainingImgPath", (voidP)(new string("")), ECF::STRING);
	state->getRegistry()->registerEntry("validationImgPath", (voidP)(new string("")), ECF::STRING);
	state->getRegistry()->registerEntry("includeCentralPixel", (voidP)(new int(1)), ECF::INT);
	state->getRegistry()->registerEntry("errorPower", (voidP)(new int(1)), ECF::INT);
}

bool ImageProcessingOp::initialize(StateP state)
{
	std::stringstream ss;
	std::string names, name;
	voidP sptr;

	ConvolutionParamsP convParams(new ConvolutionParams());
	this->params = convParams;

	// Image parameters
	sptr = state->getRegistry()->getEntry("imageWidth");
	this->params->width = *((int *)sptr.get());
	sptr = state->getRegistry()->getEntry("imageHeight");
	this->params->height = *((int *)sptr.get());
	sptr = state->getRegistry()->getEntry("imageMaxValue");
	this->imageMaxValue = *((double *)sptr.get());
	sptr = state->getRegistry()->getEntry("imageMinValue");
	this->imageMinValue = *((double *)sptr.get());
	sptr = state->getRegistry()->getEntry("errorPower");
	this->errorPower = *((int *)sptr.get());

	// Convolution parameters
	sptr = state->getRegistry()->getEntry("convolutionSize");
	this->params->convolutionSize = *((int *)sptr.get());
	sptr = state->getRegistry()->getEntry("sizePercentage");
	this->params->percentage = *((double *)sptr.get());
	sptr = state->getRegistry()->getEntry("includeCentralPixel");
	this->params->includeCentralPixel = *((int *)sptr.get());

	// Calculate params for submatrix search
	this->params->delta = this->params->convolutionSize / 2;
	this->params->imageSize = (int)(this->params->height * this->params->width * this->params->percentage);

	// Number of rows and cols for submatrix search
	this->params->nRows = (int)(sqrt(this->params->imageSize));
	this->params->nCols = this->params->nRows;

	// Submatrix starting position on the image
	this->params->rowStart = (int)(this->params->height / 2. - this->params->nRows / 2.); //(int)rng::get_unifrom_random_uint(0, this->params->height - this->params->nRows);
	this->params->colStart = (int)(this->params->width / 2. - this->params->nCols / 2.);  //(int)rng::get_unifrom_random_uint(0, this->params->width - this->params->nCols);

	// Target images
	sptr = state->getRegistry()->getEntry("targetImgPath");
	names = *((std::string *)sptr.get());
	ss.str("");
	ss.clear();
	ss << names;
	name = "";
	while (ss >> name)
	{
		cout << name << endl;
		auto targetImage = IP::loadImageFromVector(name.c_str());
		this->targetImages.push_back(targetImage);

		// Precalculate target pixels for each target image
		vector<double> result;
		IP::getTagretImageConvolutionPixels(targetImage, result, this->params);
		this->targetImagesConvolutionPixels.push_back(result);
	}

	// Training images
	sptr = state->getRegistry()->getEntry("trainingImgPath");
	names = *((std::string *)sptr.get());
	ss.str("");
	ss.clear();
	ss << names;
	name = "";
	while (ss >> name)
	{
		auto trainingImage = IP::loadImageFromVector(name.c_str());
		this->trainingImages.push_back(trainingImage);

		// Precalculate convolution inputs for each training image
		vector<vector<double>> convolutionInputs;
		IP::getConvolutionInputs(trainingImage, convolutionInputs, this->params);
		this->convolutionInputsForImages.push_back(convolutionInputs);
	}

	// Validation images
	sptr = state->getRegistry()->getEntry("validationImgPath");
	names = *((std::string *)sptr.get());
	ss.str("");
	ss.clear();
	ss << names;
	name = "";
	while (ss >> name)
	{
		auto validationImage = IP::loadImageFromVector(name.c_str());
		this->validationImages.push_back(validationImage);
	}

	return true;
}

FitnessP ImageProcessingOp::evaluate(IndividualP individual)
{
	cartesian::Cartesian *cartesian = (cartesian::Cartesian *)individual->getGenotype().get();
	FitnessP fitness(new FitnessMin);
	double error = 0.;

	for (int i = 0, n = targetImagesConvolutionPixels.size(); i < n; i++)
	{
		vector<vector<double>> convolutionInputs = convolutionInputsForImages[i];
		vector<double> generatedImage;

		for (int j = 0, m = convolutionInputs.size(); j < m; j++)
		{
			vector<double> convolutionResult;
			cartesian->evaluate(convolutionInputs[j], convolutionResult);
			double output = abs(convolutionResult[0]);
			generatedImage.push_back(output);
		}

		// vector<double> result;
		// vector<double> targetImage = targetImagesConvolutionPixels[i];
		// IP::fixInvalidValues(generatedImage, this->imageMinValue, this->imageMaxValue);
		// for (int pixel = 0, k = generatedImage.size(); pixel < k; pixel++) {
		// 	result.push_back(targetImage[pixel] - generatedImage[pixel]);
		// }

		vector<double> targetImage = targetImagesConvolutionPixels[i];
		double imageError = IP::calculateError(generatedImage, targetImage, this->errorPower);

		error += pow(imageError, 1. / this->errorPower) / ((int)(this->params->width * this->params->height * this->params->percentage));
		if (!std::isfinite(error))
		{
			error = 10e6;
			break;
		}
	}

	error /= trainingImages.size();
	fitness->setValue(error);
	return fitness;
}


// FitnessP ImageProcessingOp::evaluate(IndividualP individual)
// {
// 	FitnessP fitness(new FitnessMin);

// 	cartesian::Cartesian *cartesian = (cartesian::Cartesian *)individual->getGenotype().get();

// 	//average value of y and t
// 	double mean_y = 0, mean_t = 0, sum_yt = 0, sum_sqr_y = 0, y;
// 	int nSamples = targetImagesConvolutionPixels.size() * convolutionInputsForImages[0].size();
// 	for (int i = 0; i < targetImagesConvolutionPixels.size(); i++)
// 	{
// 		vector<vector<double>> convolutionInputs = convolutionInputsForImages[i];
// 		vector<double> targetImage = targetImagesConvolutionPixels[i];

// 		for (int j = 0, m = convolutionInputs.size(); j < m; j++)
// 		{
// 			vector<double> convolutionResult;
// 			cartesian->evaluate(convolutionInputs[j], convolutionResult);
// 			y = abs(convolutionResult[0]);

// 			// clip the value to [0, 255]
// 			y = (int)abs(y);
// 			if (y > 255)
// 				y = 255;

// 			mean_y += y;
// 			double t = targetImage[j];
// 			mean_t += t;
// 			sum_yt += t * y;
// 			sum_sqr_y += y * y;
// 		}
// 	}

// 	mean_y /= nSamples;
// 	mean_t /= nSamples;

// 	// coefficients for linear regression
// 	double b = (sum_yt - nSamples * mean_y * mean_t) / (sum_sqr_y - nSamples * mean_y * mean_y);
// 	double a = mean_t - b * mean_y;

// 	if (!std::isfinite(a) || !std::isfinite(b))
// 	{
// 		a = 0;
// 		b = 1;
// 	}

// 	double value = 0;
// 	double var_of_y = 0; // variance of variable result

// 	for (int i = 0; i < targetImagesConvolutionPixels.size(); i++)
// 	{
// 		vector<vector<double>> convolutionInputs = convolutionInputsForImages[i];
// 		vector<double> targetImage = targetImagesConvolutionPixels[i];

// 		for (int j = 0, m = convolutionInputs.size(); j < m; j++)
// 		{
// 			vector<double> convolutionResult;
// 			cartesian->evaluate(convolutionInputs[j], convolutionResult);
// 			y = abs(convolutionResult[0]);

// 			// clip the value to [0, 255]
// 			y = (int)abs(y);
// 			if (y > 255)
// 				y = 255;

// 			var_of_y += (y - mean_y) * (y - mean_y);
// 			double result = a + b * y;
// 			result = (int)result;

// 			double error = abs(targetImage[j] - result);
// 			value += error;
// 		}
// 	}

// 	value /= nSamples;
// 	fitness->setValue(value);

// 	return fitness;
// }

#include "ImageProcessingOp.h"

ImageProcessingOp::ImageProcessingOp(){}

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
	state->getRegistry()->registerEntry("includeCentralPixel", (voidP)(new int(1)), ECF::INT);
}

bool ImageProcessingOp::initialize(StateP state)
{
	std::stringstream ss;
    std::string names, name;
	voidP sptr;
	
	// Image parameters
	sptr = state->getRegistry()->getEntry("imageWidth");
	this->imageWidth = *((int*)sptr.get());
	sptr = state->getRegistry()->getEntry("imageHeight");
	this->imageHeight = *((int*)sptr.get());
	sptr = state->getRegistry()->getEntry("imageMaxValue");
	this->imageMaxValue = *((double*)sptr.get());
	sptr = state->getRegistry()->getEntry("imageMinValue");
	this->imageMinValue = *((double*)sptr.get());

	// Convolution parameters
	sptr = state->getRegistry()->getEntry("convolutionSize");
	this->convolutionSize = *((int*)sptr.get());
	sptr = state->getRegistry()->getEntry("sizePercentage");
	this->sizePercentage = *((double*)sptr.get());
	sptr = state->getRegistry()->getEntry("includeCentralPixel");
	this->includeCentralPixel = *((int*)sptr.get());

	// Target images
	sptr = state->getRegistry()->getEntry("targetImgPath");
    names = *((std::string*) sptr.get());
    ss.str("");
    ss.clear();
    ss << names;
    name="";
    while(ss >> name) {
		cout << name << endl;
        auto targetImage = IP::loadImageFromVector(name.c_str());
		this->targetImages.push_back(targetImage);
    }

	// Training images
	sptr = state->getRegistry()->getEntry("trainingImgPath");
    names = *((std::string*) sptr.get());
    ss.str("");
    ss.clear();
    ss << names;
    name="";
    while(ss >> name) {
        auto trainingImage = IP::loadImageFromVector(name.c_str());
		this->trainingImages.push_back(trainingImage);
    }

	return true;
}


FitnessP ImageProcessingOp::evaluate(IndividualP individual)
{
	cartesian::Cartesian* cartesian = (cartesian::Cartesian*) individual->getGenotype().get();
	FitnessP fitness(new FitnessMin);
	double error = 0.;
	
	for (int i = 0, n = trainingImages.size(); i < n;  i++) {
		vector<double> trainingImage = trainingImages[i];
		vector<double> generatedImage;

		IP::convolution(trainingImage, generatedImage, this->imageWidth, this->imageHeight, cartesian,
						this->convolutionSize, this->sizePercentage, this->offsetPercentage);

		vector<double> result;
		vector<double> targetImage = this->targetImages[i];
		IP::fixInvalidValues(generatedImage, this->imageMinValue, this->imageMaxValue);
		for (int pixel = 0; pixel < generatedImage.size(); pixel++) {
			result.push_back(targetImage[pixel] - generatedImage[pixel]);
		}

		error += IP::euclideanNorm(result) / (this->imageWidth * this->imageHeight * this->imageMaxValue * this->imageMaxValue * this->sizePercentage);
		if (!std::isfinite(error)) {
			error = 10e6;
			break;
		}
		
	}

	fitness->setValue(error);
	return fitness;

}

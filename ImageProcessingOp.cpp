#include "ImageProcessingOp.h"

ImageProcessingOp::ImageProcessingOp(){}

bool ImageProcessingOp::initialize(StateP)
{
	auto originalImage = IP::loadImageFromVector("./data/lenna.txt");
	//IP::scale(originalImage, 255);

	auto trainingImage = IP::loadImageFromVector("./data/lenna-noised.txt");

	this->original_images.push_back(originalImage);
	this->training_data.push_back(trainingImage);

	return true;
}


FitnessP ImageProcessingOp::evaluate(IndividualP individual)
{
	cartesian::Cartesian* cartesian = (cartesian::Cartesian*) individual->getGenotype().get();
	FitnessP fitness(new FitnessMin);
	double error = 0.;
	double percentage = 0.01;
	double offset_perc = 0.;

	for (int i = 0, n = training_data.size(); i < n;  i++) {
		
		vector<double> image = training_data[i];
		vector<double> generatedImage;

		IP::convolution(image, generatedImage, IP::IMG_WIDTH, IP::IMG_HEIGHT, cartesian, 5, percentage, offset_perc);

		vector<double> result;
		vector<double> original_image = this->original_images[i];
		IP::fixInvalidValues(generatedImage);
		for (int pixel = 0; pixel < generatedImage.size(); pixel++) {
			result.push_back(original_image[pixel] - generatedImage[pixel]);
		}

		error += IP::euclideanNorm(result) / (IP::IMG_HEIGHT * IP::IMG_WIDTH * 255. * 255. * percentage);

		// Black image 
		//error -= 0.5 * (IP::euclideanNorm(generatedImage) / (784. * 255 * 255));

		/*vector<double> difference;
		for (int pixel = 0; pixel < image.size(); pixel++) {
			difference.push_back(image[pixel] - generatedImage[pixel]);
		}
		error -= (IP::absoluteSum(difference) / (784. * 255 * 255));*/

		if (!std::isfinite(error)) {
			error = 10e6;
			break;
		}
		
	}

	fitness->setValue(error);
	return fitness;

}

#include "ImageProcessingOp.h"

ImageProcessingOp::ImageProcessingOp(){}

bool ImageProcessingOp::initialize(StateP)
{
	// FOR NOISED TRAINING
	//std::uniform_real_distribution<double> dist(0, 1);
	//for (auto image : data) {
	//	vector<double> originalImage(image);
	//	IP::scale(originalImage, 255);
	//	this->original_images.push_back(originalImage);
	//	// Add noise to original image
	//	int imgSize = image.size();
	//	int nRows = 28;
	//	for (int row = 0; row < nRows; row += 2) {
	//		// Add noise such that neighbourhood is perserved
	//		for (int col = 0; col < 5; col++) {
	//			int index = row * 28 + col * 5;
	//			if (row % 4)
	//				index += 4;
	//			else
	//				index += 2;
	//			image[index] = 0.5;
	//		}
	//	}
	//	IP::scale(image, 255);
	//	this->training_data.push_back(image);
	//}

	// FOR MOTION BLUR TRAINING

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

	for (int i = 0, n = training_data.size(); i < n;  i++) {
		
		vector<double> image = training_data[i];
		vector<double> generatedImage;

		IP::convolution(image, generatedImage, IP::IMG_WIDTH, IP::IMG_HEIGHT, cartesian, 3, percentage);

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

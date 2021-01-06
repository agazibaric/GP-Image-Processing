#include "AdversarialOp.h"

AdversarialOp::AdversarialOp(){}

bool AdversarialOp::initialize(StateP)
{
	// Load model that will be attacked with adverasrial examples
	//this->targetModel = MNIST::loadModel("./models/net1.pt");

	this->target = 5;
	//this->fakeTarget = 6;
	// Load MNIST data that represents target number
	auto data = MNIST::loadTargetData(this->target);

	// FOR NOISED TRAINING
	//std::uniform_real_distribution<double> dist(0, 1);
	//for (auto image : data) {
	//	vector<double> originalImage(image);
	//	MNIST::scale(originalImage, 255);
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
	//	MNIST::scale(image, 255);
	//	this->training_data.push_back(image);
	//}

	// FOR MOTION BLUR TRAINING
	auto originalImage = data[0];
	MNIST::scale(originalImage, 255);

	auto trainingImage = MNIST::loadImageFromVector("blured-vert.txt");

	this->original_images.push_back(originalImage);
	this->training_data.push_back(trainingImage);

	return true;
}


FitnessP AdversarialOp::evaluate(IndividualP individual)
{
	cartesian::Cartesian* cartesian = (cartesian::Cartesian*) individual->getGenotype().get();
	FitnessP fitness(new FitnessMin);
	double error = 0.;

	for (int i = 0, n = training_data.size(); i < n;  i++) {
		
		vector<double> image = training_data[i];
		vector<double> generatedImage;

		MNIST::convolution(image, generatedImage, MNIST::IMG_WIDTH, MNIST::IMG_HEIGHT, cartesian, 5);

		vector<double> result;
		vector<double> original_image = this->original_images[i];
		MNIST::fixInvalidValues(generatedImage);
		for (int pixel = 0; pixel < generatedImage.size(); pixel++) {
			result.push_back(original_image[pixel] - generatedImage[pixel]);
		}

		error += MNIST::euclideanNorm(result) / (784. * 255 * 255);

		// Black image 
		//error -= 0.5 * (MNIST::euclideanNorm(generatedImage) / (784. * 255 * 255));

		/*vector<double> difference;
		for (int pixel = 0; pixel < image.size(); pixel++) {
			difference.push_back(image[pixel] - generatedImage[pixel]);
		}
		error -= (MNIST::absoluteSum(difference) / (784. * 255 * 255));*/


		// Create adversarial image by combining original image and adversarial filter
		//vector<double> adversarialImage = MNIST::combine(image, filter);
		//MNIST::fixInvalidValues(generatedImage);

		// Attack target model with adversarial image
		/*torch::Tensor tensor = MNIST::vectorToTensor(generatedImage);
		torch::Tensor normalized = MNIST::normalize(tensor);
		torch::Tensor prediction = this->targetModel->forward(normalized);*/

		// Evalute adversarial image
		/*torch::Tensor fakeTarget = torch::tensor({ this->fakeTarget });
		torch::Tensor loss = torch::nll_loss(prediction, fakeTarget);
		loss = loss.view({ 1 });
		double lossWeight = 1;
		double lossComponent = lossWeight * loss[0].item<float>();
		error += lossComponent;*/

		/*int predictionValue = prediction.argmax().view({ 1 })[0].item<int>();
		if (predictionValue != this->fakeTarget) {
			error += 1;
		}*/

		// Evaluate adversarial filter
		/*double filterWeight = 10;
		double filterNorm = MNIST::euclideanNorm(filter);
		double filterComponent = filterWeight * filterNorm;
		error += filterComponent;*/

		if (!std::isfinite(error)) {
			error = 10e6;
			break;
		}
		
	}

	fitness->setValue(error);
	return fitness;

}

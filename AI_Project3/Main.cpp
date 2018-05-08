// Michael Sousa COMP 470 Project 3

#include "NeuralNetwork.hpp"


int main() {
	srand((unsigned int)time(NULL));

	NeuralNetwork* neural_net = new NeuralNetwork();
	std::string input;

	//testing single epoch in network
	std::vector<double> test_input = neural_net->getData()[0];
	double target = neural_net->getTargetValues()[0];

	std::cout << "Initial Network" << std::endl;
	neural_net->printNetwork();

	//neural_net->feedForward(test_input);
	//neural_net->backPropagation(target);

	//neural_net->printNetwork();
	
	// train on data
	for (int i = 0; i < Options::epochs; i++) {
		// train on first class of data
		neural_net->trainNeuralNet(neural_net->getData()[i],neural_net->getTargetValues()[i]);
		if (i == Options::epochs - 1) {
			std::cout << "Network after training on class 1 data (Target -1)" << std::endl;
			neural_net->printNetwork();
		}
		/*
		// train on second class of data
		neural_net->trainNeuralNet(neural_net->getData()[i + 50], neural_net->getTargetValues()[i + 50]);
		if (i == Options::epochs - 1) {
			std::cout << "Network after training on class 2 data (Target 0)" << std::endl;
			neural_net->printNetwork();
		}
		// train on third class of data
		neural_net->trainNeuralNet(neural_net->getData()[i + 100], neural_net->getTargetValues()[i + 100]);
		if (i == Options::epochs - 1) {
			std::cout << "Network after training on class 3 data (Target 1)" << std::endl;
			neural_net->printNetwork();
		}
		*/
	}
	
	// test data
	/*
	for (int i = 0; i < Options::test_net; i++) {
		// test on first class of data
		neural_net->testNeuralNet(neural_net->getData()[Options::epochs + i], neural_net->getClasses()[Options::epochs + i]);
		// test on second class of data
		neural_net->testNeuralNet(neural_net->getData()[Options::epochs + i + 50], neural_net->getClasses()[Options::epochs + i + 50]);
		// test on third class of data
		neural_net->testNeuralNet(neural_net->getData()[Options::epochs + i + 100], neural_net->getClasses()[Options::epochs + i + 100]);
	}
	*/
	/*
	// debug for first class
	for (int i = 0; i < Options::epochs; i++) {
		// train on first class of data
		neural_net->trainNeuralNet(neural_net->getData()[i], neural_net->getTargetValues()[i]);
	}
	std::cout << "Network after training on class 1 data (Target -1)" << std::endl;
	neural_net->printNetwork();

	// debug for second class
	for (int i = 0; i < Options::epochs; i++) {
		// train on first class of data
		neural_net->trainNeuralNet(neural_net->getData()[i + 50], neural_net->getTargetValues()[i + 50]);
	}
	std::cout << "Network after training on class 2 data (Target 0)" << std::endl;
	neural_net->printNetwork();

	// debug for third class
	for (int i = 0; i < Options::epochs; i++) {
		// train on first class of data
		neural_net->trainNeuralNet(neural_net->getData()[i + 100], neural_net->getTargetValues()[i + 100]);
	}
	std::cout << "Network after training on class 3 data (Target 1)" << std::endl;
	neural_net->printNetwork();
	*/
	if (Options::debug) {
		neural_net->printNetwork();
		//neural_net->printData();
	}
	
	do {
		input = "";
		std::cout << "1. Neural Network" << std::endl;
		std::cout << "q. Quit" << std::endl;
		getline(std::cin, input);

		if (input == "1") {
			neural_net->printNetwork();
		}

	} while (input != "q");
}
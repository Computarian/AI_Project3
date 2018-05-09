// Michael Sousa COMP 470 Project 3

#include "NeuralNetwork.hpp"

void runNeuralNetwork();


int main() {
	srand((unsigned int)time(NULL));
	NeuralNetwork* stats = new NeuralNetwork();
	stats->initializeStats();

	std::string input;

	std::cout << "~~~~Iris Neural Network~~~~" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

	do {
		input = "";
		std::cout << std::endl;
		std::cout << "1. Run Iris Neural Networks" << std::endl;
		std::cout << "q. Quit" << std::endl;
		getline(std::cin, input);

		if (input == "1") {
			for (int i = 0; i < Options::cycles; i++) {
				runNeuralNetwork();
			}
			stats->printStats();
		}

	} while (input != "q");
}


void runNeuralNetwork() {
	NeuralNetwork* neural_net_setosa = new NeuralNetwork();
	NeuralNetwork* neural_net_versicolor = new NeuralNetwork();
	NeuralNetwork* neural_net_virginica = new NeuralNetwork();

	// train on data
	for (int i = 0; i < Options::epochs; i++) {
		// train on first class of data
		neural_net_setosa->trainNeuralNet(neural_net_setosa->getData()[i], neural_net_setosa->getTargetValues()[i]);

		// train on second class of data
		neural_net_versicolor->trainNeuralNet(neural_net_versicolor->getData()[i + 50], neural_net_versicolor->getTargetValues()[i + 50]);

		// train on third class of data
		neural_net_virginica->trainNeuralNet(neural_net_virginica->getData()[i + 100], neural_net_virginica->getTargetValues()[i + 100]);
	}
	if (Options::debug) {
		// debug for first class
		std::cout << "Network after training on class 1 data (Target -1)" << std::endl;
		neural_net_setosa->printNetwork();

		// debug for second class
		std::cout << "Network after training on class 2 data (Target 0)" << std::endl;
		neural_net_versicolor->printNetwork();

		// debug for third class
		std::cout << "Network after training on class 3 data (Target 1)" << std::endl;
		neural_net_virginica->printNetwork();
	}
	// test data
	for (int i = 0; i < Options::test_net; i++) {
		// test on first class of data
		neural_net_setosa->testNeuralNet(neural_net_setosa->getData()[Options::epochs + i], neural_net_setosa->getClasses()[Options::epochs + i]);
		// test on second class of data
		neural_net_versicolor->testNeuralNet(neural_net_versicolor->getData()[Options::epochs + i + 50], neural_net_versicolor->getClasses()[Options::epochs + i + 50]);
		// test on third class of data
		neural_net_virginica->testNeuralNet(neural_net_virginica->getData()[Options::epochs + i + 100], neural_net_virginica->getClasses()[Options::epochs + i + 100]);
	}
}
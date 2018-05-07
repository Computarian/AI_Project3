// Michael Sousa COMP 470 Project 3

#include "NeuralNetwork.hpp"


int main() {
	srand((unsigned int)time(NULL));

	NeuralNetwork* neural_net = new NeuralNetwork();
	std::string input;

	//testing single epoch in network
	std::vector<double> test_input = neural_net->getData()[0];
	double target = neural_net->getTargetValues()[0];
	neural_net->feedForward(test_input);
	neural_net->backPropagation(target);
	if (Options::debug) {
		//neural_net->printNetwork();
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
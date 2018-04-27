// Michael Sousa COMP 470 Project 3


#include "NeuralNetwork.hpp"

int main() {
	srand((unsigned int)time(NULL));

	int num_inputs = 4;
	int num_hidden_layers = 2;
	NeuralNetwork* neural_net = new NeuralNetwork(num_inputs, num_hidden_layers);
	std::string input;

	do {
		input = "";
		std::cout << "1. Neural Network" << std::endl;
		std::cout << "q. Quit" << std::endl;
		getline(std::cin, input);

		if (input == "1") {
			neural_net->printNetwork();
			neural_net->testSum();

			neural_net->printResults();
		}

	} while (input != "q");
}
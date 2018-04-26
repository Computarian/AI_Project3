// Michael Sousa COMP 470 Project 3


#include "NeuralNetwork.hpp"

int main() {
	NeuralNetwork* neural_net = new NeuralNetwork();
	std::string input;

	do {
		input = "";
		std::cout << "1. Neural Network" << std::endl;
		std::cout << "q. Quit" << std::endl;
		getline(std::cin, input);

		if (input == "1") {
			neural_net->printResults();
		}

	} while (input != "q");
}
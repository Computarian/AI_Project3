#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include "Neuron.hpp"
#include <iostream>
#include <string>

class NeuralNetwork {

public:
	NeuralNetwork(int num_inputs, int num_hidden_layers);

	void testSum();
	void printNetwork();
	void printResults();
	
private:
	int num_inputs_;
	int num_outputs_;
	int num_hidden_layers_;
	std::vector<Neuron*> input_layer_;
	std::vector<Neuron*> output_layer_;
	std::vector<std::vector<Neuron*>> hidden_layers_;

};

#endif //NEURAL_NETWORK_HPP
#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include "Neuron.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

class NeuralNetwork {

public:
	NeuralNetwork(int num_inputs, int num_hidden_layers);
	void readData();
	void printData();
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
	std::vector<std::vector<double>> data_set_;

};

#endif //NEURAL_NETWORK_HPP
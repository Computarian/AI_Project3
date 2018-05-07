#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include "Neuron.hpp"
#include "Options.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>


class NeuralNetwork {

public:
	NeuralNetwork();

	void readData();
	std::vector<std::vector<double>> getData();
	std::vector<double> getTargetValues();

	void feedForward(std::vector<double> &input_values);
	void backPropagation(double target_value);
	void getResults();

	void printNetwork();
	void printData();

private:
	int num_inputs_;
	int num_hidden_;
	int num_hidden_layers_;
	int total_layers_; 
	int sum_data_;
	double current_output_;

	std::vector<Neuron*> input_layer_;
	Neuron* output_layer_;
	std::vector<std::vector<Neuron*>> hidden_layers_;
	std::vector<std::vector<double>> data_set_;
	std::vector<int> classes_;
	std::vector<double> target_values_;
};

#endif //NEURAL_NETWORK_HPP
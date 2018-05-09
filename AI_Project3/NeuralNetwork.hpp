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
	std::vector<int> getClasses();
	std::vector<double> getTargetValues();

	void feedForward(std::vector<double> &input_values);
	void backPropagation(double target_value);
	void clearNeuralNetworkValues();

	// train neural net by running feed forward and then back propagation
	void trainNeuralNet(std::vector<double> &input_values, double target_value);
	// test neural net by using feed forward after training and classifying output
	void testNeuralNet(std::vector<double> &input_values, int actual_class);

	void initializeStats();

	void printNetwork();
	void printData();
	void printStats();

private:
	int num_inputs_;
	int num_hidden_;
	int num_hidden_layers_;
	int total_layers_; 
	int sum_data_;
	static int correct_guesses_;
	static int total_guesses_;

	// neural net layers
	std::vector<Neuron*> input_layer_;
	Neuron* output_layer_;
	std::vector<std::vector<Neuron*>> hidden_layers_;
	// data set
	std::vector<std::vector<double>> data_set_;
	std::vector<int> classes_;
	std::vector<double> target_values_;
	// delta values
	std::vector<double> delta_output_;
	std::vector<std::vector<std::vector<double>>> delta_hidden_;
	std::vector<std::vector<double>> delta_input_;
};

#endif //NEURAL_NETWORK_HPP
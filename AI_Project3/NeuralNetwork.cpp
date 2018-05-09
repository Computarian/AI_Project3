#include "NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(){
	this->num_inputs_ = Options::num_inputs;
	this->num_hidden_ = Options::num_hidden;
	this->num_hidden_layers_ = Options::num_hidden_layers;

	// read in the data set
	readData();

	// initializing input layer
	for (int i = 0; i < num_inputs_; i++) {
		Neuron* input_neuron = new Neuron();
		input_layer_.push_back(input_neuron);
	}
	
	// initializing hidden layers
	for (int i = 0; i < num_hidden_layers_; i++) {
		std::vector<Neuron*> hidden_layer;
		hidden_layers_.push_back(hidden_layer);
		for (int j = 0; j < num_inputs_ + 1; j++) {
			Neuron* hidden_neuron = new Neuron();
			hidden_layers_[i].push_back(hidden_neuron);
		}
	}

	// initializing output
	this->output_layer_ = new Neuron();

	// initializing synapse weights input layer to first hidden layer
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < num_hidden_; j++) {
			input_layer_[i]->addSynapse(-1 + 2 * ((double)rand()) / RAND_MAX);
			input_layer_[i]->getSynapse(j)->setTo(hidden_layers_[0][j]);
		}
	}

	// initializing synapse weights between hidden layers
	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		for (unsigned int j = 0; j < hidden_layers_[i].size(); j++) {
			for (unsigned int k = 0; k < hidden_layers_[i+1].size(); k++) {
				hidden_layers_[i][j]->addSynapse(-1 + 2 * ((double)rand()) / RAND_MAX);
				hidden_layers_[i][j]->getSynapse(k)->setTo(hidden_layers_[i + 1][k]);
			}
		}
	}
	
	// initializing synapse weights from final hidden layer to output layer
	for (int i = 0; i < num_hidden_; i++) {
			hidden_layers_.back()[i]->addSynapse(-1 + 2 * ((double)rand()) / RAND_MAX);
			hidden_layers_.back()[i]->getSynapse(0)->setTo(output_layer_);
	}
}


void NeuralNetwork::readData() {
	this->sum_data_ = 0;

	//The name of our file
	const std::string data = "iris.data";

	//Our input file stream
	std::ifstream inputFile(data.c_str());
	//Make sure it opened correctly
	if (inputFile.is_open()) {
		//Buffer that will store a single line from the file
		std::string lineFromFile;

		//Read the first line from the file, store in "lineFromFile"
		while (getline(inputFile, lineFromFile)) {
			//Buffer that will store a single piece of data from our line
			std::string token;

			//Stores the converted tokens
			std::vector<double> data_row;

			//Create a stringstream using the line we got from the file
			std::stringstream myStream(lineFromFile);

			// Only want the first 4 (num of inputs) values from the data set (5th is flower name) 
			int counter = 0;
			//Loop until we have parsed this entire line
			while (getline(myStream, token, ',')) {
				if (counter < num_inputs_) {
					double datum = stod(token);
					data_row.push_back(datum);
				}
				counter++;
			}
			this->data_set_.push_back(data_row);
			data_row.clear();

			// classifying iris data set
			if (sum_data_ < 50) {
				classes_.push_back(1);
				target_values_.push_back(-1);
			}
			else if (sum_data_ < 100) {
				classes_.push_back(2);
				target_values_.push_back(0);
			}
			else {
				classes_.push_back(3);
				target_values_.push_back(1);
			}
			this->sum_data_++;
		}
	}
	inputFile.close();
}


std::vector<std::vector<double>> NeuralNetwork::getData() {
	return this->data_set_;
}


std::vector<int> NeuralNetwork::getClasses() {
	return this->classes_;
}


std::vector<double> NeuralNetwork::getTargetValues() {
	return this->target_values_;
}


void NeuralNetwork::printNetwork() {
	std::cout << "Input Layer Values" << std::endl;
	// print values of input layer
	for (int i = 0; i < num_inputs_; i++) {
		std::cout << "I: N" << i << " " << input_layer_[i]->getOutputValue() << std::endl;
	}

	std::cout << "Synapse weights to Hidden Layer " << 0 << std::endl;
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < input_layer_[i]->getNumberOfSynapses(); j++) {
			std::cout << "I: N" << i << ": Synapse " << j << ": Weight ";
			std::cout << input_layer_[i]->getSynapse(j)->getWeight() << std::endl;
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		std::cout << "Hidden Layer " << i << " Values" << std::endl;
		// print values of hidden layer neurons
		for (int j = 0; j < num_hidden_; j++) {
			std::cout << "H" << i << ": N" << j << " " << hidden_layers_[i][j]->getOutputValue() << std::endl;
		}
		std::cout << "Synapse weights to Hidden Layer " << i + 1 << std::endl;
		for (int j = 0; j < num_hidden_; j++) {
			for (int k = 0; k < hidden_layers_[i][j]->getNumberOfSynapses(); k++) {
				std::cout << "H" << i << ": N" << j << ": Synapse " << k << ": Weight ";
				std::cout << hidden_layers_[i][j]->getSynapse(k)->getWeight() << std::endl;
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Hidden Layer " << num_hidden_layers_ - 1 << " Values" << std::endl;
	// prints values of final hidden layer
	for (int i = 0; i < num_hidden_ ; i++) {
		std::cout << "H" << num_hidden_layers_ - 1 << " N" << i << " ";
		std::cout << hidden_layers_[num_hidden_layers_ - 1][i]->getOutputValue() << std::endl;
	}
	std::cout << "Synapses weights to Output Layer" << std::endl;
	for (int i = 0; i < num_hidden_; i++) {
		std::cout << "H" << num_hidden_layers_ - 1 << ": N" << i << ": Synapse " << 0 << ": Weight ";
		std::cout << hidden_layers_.back()[i]->getSynapse(0)->getWeight() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Output Layer Value" << std::endl;
	// prints values of output layer
	std::cout << "O: N0: " << output_layer_->getOutputValue() << std::endl;
	std::cout << std::endl;
}


void NeuralNetwork::printData() {
	for (int i = 0; i < sum_data_ - 1; i++) {
		std::cout << std::right << std::setw(3) << std::setfill(' ');
		std::cout << i << ": " << "Class: " << classes_[i] << " Target: "<< target_values_[i] << " Data: ";
		for (int j = 0; j < num_inputs_; j++) {
			std::cout << std::setprecision(1) << std::fixed;
			std::cout <<data_set_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void NeuralNetwork::feedForward(std::vector<double> &input_values) {
	// loop through data and loop through input layers
	for (int i = 0; i < num_inputs_; i++) {
		input_layer_[i]->setOutputValue(input_values[i]);
		if (Options::debug) {
			std::cout <<"I: N" << i <<": Value " << input_layer_[i]->getOutputValue() << std::endl;
		}
	}
	// calculate first hidden layer values (input->hidden layer 1)
	for (int i = 0; i < num_hidden_; i++) {
		for (int j = 0; j < num_inputs_; j++) {
			double value = input_layer_[j]->getSynapse(i)->getWeight() * input_layer_[j]->getOutputValue();
			hidden_layers_[0][i]->addToSum(value);
		}
		if (Options::debug) {
			std::cout << "H" << 0 << ": N" << i << ": Before Activation " << hidden_layers_[0][i]->getSummedValue() << std::endl;
		}
		hidden_layers_[0][i]->computeValue();
		if (Options::debug) {
			std::cout << "H" << 0 << ": N" << i << ": After Activation " << hidden_layers_[0][i]->getOutputValue() << std::endl;
		}
	}
	// calculate all other hidden layer values
	for (int i = 1; i < num_hidden_layers_; i++) {
		for (int j = 0; j < num_hidden_; j++) {
			for (int k = 0; k < hidden_layers_[i - 1][j]->getNumberOfSynapses(); k++) {
				double value = hidden_layers_[i - 1][k]->getSynapse(j)->getWeight() * hidden_layers_[i - 1][k]->getOutputValue();
				//std::cout << "current synapse * previous layer value " << value << std::endl;
				hidden_layers_[i][j]->addToSum(value);
			}
			if (Options::debug) {
				std::cout << "H" << i <<": N"<<j<<": Before Activation " << hidden_layers_[i][j]->getSummedValue() << std::endl;
			}
			hidden_layers_[i][j]->computeValue();
			if (Options::debug) {
				std::cout << "H" << i << ": N" << j << ": After Activation " << hidden_layers_[i][j]->getOutputValue() << std::endl;
			}
		}
	}
	// calculate output layer value
	for (int i = 0; i < num_hidden_; i++) {
		double value = hidden_layers_.back()[i]->getSynapse(0)->getWeight() * hidden_layers_.back()[i]->getOutputValue();
		//std::cout << "current synapse * previous layer value " << value << std::endl;
		output_layer_->addToSum(value);
	}
	if (Options::debug) {
		std::cout << "O N: " << 0 << ": Before Activation " << output_layer_->getSummedValue() << std::endl;
	}
	output_layer_->computeValue();
	if (Options::debug) {
		std::cout << "O N: " << 0 << ": After Activation " << output_layer_->getOutputValue() << std::endl;
	}
}


void NeuralNetwork::backPropagation(double target_value) {
	// clear vectors of deltas
	delta_output_.clear();
	delta_hidden_.clear();
	delta_input_.clear();

	// calculate error
	double error = target_value - output_layer_->getOutputValue();
	std::cout << "Error is " << error << std::endl;
	if (Options::debug) {
		std::cout << "Error is " << error << std::endl;
	}
	// tanh derivative of output layer output value
	double deriv_output = (target_value - output_layer_->getOutputValue() * output_layer_->getOutputValue());
	//std::cout << "output tangent derivative is " << deriv_output << std::endl;

	// calculate output layer deltas	
	for (int i = 0; i < num_hidden_; i++) {
		double delta_old_weight = deriv_output / hidden_layers_.back()[i]->getOutputValue();
		delta_output_.push_back(delta_old_weight);
	}
	
	// calculate hidden layer deltas
	/*
	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		std::vector <std::vector<double>> layer_deltas;
		delta_hidden_.push_back(layer_deltas);

		for (int j = 0; j < num_hidden_; j++) {

			for (int k = 0; k < hidden_layers_[i + 1][j]->getNumberOfSynapses(); k++) {
				double delta_hidden_to_hidden =
					(deriv_output / hidden_layers_.back()[j]->getSynapse(k)->getWeight())
					* (1.0 - tanh(hidden_layers_[i][j]->getSynapse(k)->getWeight()) * tanh(hidden_layers_[i][j]->getSynapse(k)->getWeight()));
				delta_hidden_[i][j].push_back(delta_hidden_to_hidden);
			}
		}
	}
	*/
	// calculate input layer deltas
	for (int i = 0; i < num_inputs_; i++) {
		std::vector<double> delta_input_synapses;
		delta_input_.push_back(delta_input_synapses);

		for (int j = 0; j < num_hidden_; j++) {
			double delta_input_hidden =
				(deriv_output / hidden_layers_[0][j]->getSynapse(0)->getWeight())
				* (1.0 - tanh(input_layer_[i]->getSynapse(j)->getWeight()) * tanh(input_layer_[i]->getSynapse(j)->getWeight()));
			delta_input_[i].push_back(delta_input_hidden);
		}
	}
	// print input layer to first hidden layer deltas
	/*
	for (unsigned int i = 0; i < delta_input_.size(); i++) {
		for (unsigned int j = 0; j < delta_input_[i].size(); j++) {
			std::cout << "I N" << i << ": Synapse" << j << ": delta input hidden " << delta_input_[i][j] << std::endl;
		}
	}
	*/
	// for all layers from outputs to first hidden layer
	// update synapse weights
	// update synapse weights final hidden layer to output
	for (int i = 0; i < num_hidden_; i++) {
		double new_output_weight = hidden_layers_.back()[i]->getOutputValue() + delta_output_[i];
		if (Options::debug) {
			std::cout << "O N:" << i << " Old synapse weight to output: " << hidden_layers_.back()[i]->getSynapse(0)->getWeight() << std::endl;
		}
		hidden_layers_.back()[i]->getSynapse(0)->setWeight(new_output_weight);
		if (Options::debug) {
			std::cout << "O N:" << i << " New synapse weight to output: " << hidden_layers_.back()[i]->getSynapse(0)->getWeight() << std::endl;
		}
	}
	// update synapse weights between hidden layers
	/*
	for (int i = num_hidden_layers_ - 1; ) {
		for (int j = 0; j < num_hidden_; j++) {
			for (int k = 0; k < hidden_layers_[i][j]->getNumberOfSynapses(); k++) {
				double delta_hidden_weight = delta_hidden_[i][j][k] / 
			}
		}
	}
	*/
	// update synapse weights between input and first hidden layer
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < input_layer_[i]->getNumberOfSynapses(); j++) {
			// delta input to hidden weight = delta input to hidden / input value
			double delta_input_synapse_weight = (delta_input_[i][j] / input_layer_[i]->getOutputValue());
			// new input to hidden weight = old input to hidden weight + delta input to hidden weight
			double new_input_synapse_weight = input_layer_[i]->getSynapse(j)->getWeight() + delta_input_synapse_weight;
			// update synapse between input and first hidden layer
			input_layer_[i]->getSynapse(j)->setWeight(new_input_synapse_weight);
		}
	}
}


void NeuralNetwork::clearNeuralNetworkValues() {
	// input layer gets new inputs so we can leave it alone here
	for (int i = 0; i < num_hidden_layers_; i++) {
		for (int j = 0; j < num_hidden_; j++) {
			hidden_layers_[i][j]->setSummedValue(0);
		}
	}
	output_layer_->setSummedValue(0);
}


void NeuralNetwork::trainNeuralNet(std::vector<double> &input_values, double target_value) {
		feedForward(input_values);
		backPropagation(target_value);
		clearNeuralNetworkValues();
}


void NeuralNetwork::testNeuralNet(std::vector<double> &input_values, int actual_class) {
	feedForward(input_values);
	int class_guess = output_layer_->classify();
	std::cout << "Class: " << actual_class << " Neural Net's guess: " << class_guess << std::endl;
}
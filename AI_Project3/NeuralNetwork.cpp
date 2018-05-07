#include "NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(){
	this->num_inputs_ = Options::num_inputs;
	this->num_outputs_ = Options::num_outputs;
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

	// initializing output layers
	for (int i = 0; i < num_outputs_; i++) {
		Neuron* output_neuron = new Neuron();
		output_layer_.push_back(output_neuron);
	}

	// initializing synapse weights input layer to first hidden layer
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < num_hidden_; j++) {
			input_layer_[i]->addSynapse((double)rand() / (RAND_MAX));
			input_layer_[i]->getSynapse(j)->setTo(hidden_layers_[0][j]);
		}
	}

	// initializing synapse weights between hidden layers
	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		for (unsigned int j = 0; j < hidden_layers_[i].size(); j++) {
			for (unsigned int k = 0; k < hidden_layers_[i+1].size(); k++) {
				hidden_layers_[i][j]->addSynapse((double)rand() / (RAND_MAX));
				hidden_layers_[i][j]->getSynapse(k)->setTo(hidden_layers_[i + 1][k]);
			}
		}
	}
	
	// initializing synapse weights from final hidden layer to output layer
	for (unsigned int i = 0; i < hidden_layers_.back().size(); i++) {
		for (int j = 0; j < num_outputs_; j++) {
			hidden_layers_.back()[i]->addSynapse((double)rand() / (RAND_MAX));
			hidden_layers_.back()[i]->getSynapse(j)->setTo(output_layer_[j]);
		}
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
			}
			else if (sum_data_ < 100) {
				classes_.push_back(2);
			}
			else {
				classes_.push_back(3);
			}
			this->sum_data_++;
		}
	}
	inputFile.close();
}


std::vector<std::vector<double>> NeuralNetwork::getData() {
	return this->data_set_;
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
		for (int j = 0; j < num_outputs_; j++) {
			std::cout << "H" << num_hidden_layers_ - 1 << ": N" << i << ": Synapse " << j << ": Weight ";
			std::cout << hidden_layers_.back()[i]->getSynapse(j)->getWeight() << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "Output Layer Values" << std::endl;
	// prints values of output layer
	for (int i = 0; i < num_outputs_; i++) {
		std::cout << "O: N" << i << " " << output_layer_[i]->getOutputValue() << std::endl;
	}
	std::cout << std::endl;
}


void NeuralNetwork::printData() {
	for (int i = 0; i < sum_data_ - 1; i++) {
		std::cout << std::right << std::setw(3) << std::setfill(' ');
		std::cout << i << ": " << "Class: " << classes_[i] << " Data: ";
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
			std::cout << "H" << 0 << ": N" << i << ": After Activation " << hidden_layers_[0][i]->getComputedValue() << std::endl;
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
				std::cout << "H" << i << ": N" << j << ": After Activation " << hidden_layers_[i][j]->getComputedValue() << std::endl;
			}
		}
	}
	// calculate output layer values
	for (int i = 0; i < num_outputs_; i++) {
		for (int j = 0; j < num_hidden_; j++) {
			double value = hidden_layers_.back()[j]->getSynapse(i)->getWeight() * hidden_layers_.back()[j]->getOutputValue();
			//std::cout << "current synapse * previous layer value " << value << std::endl;
			output_layer_[i]->addToSum(value);
		}
		if (Options::debug) {
			std::cout << "O N: "<<i<<": Before Activation " << output_layer_[i]->getSummedValue() << std::endl;
		}
		output_layer_[i]->computeValue();
		if (Options::debug) {
			std::cout << "O N: " << i << ": After Activation " << output_layer_[i]->getComputedValue() << std::endl;
		}
	}
}


void NeuralNetwork::backPropagation() {

}
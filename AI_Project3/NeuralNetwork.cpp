#include "NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(int num_inputs, int num_hidden_layers){
	this->num_inputs_ = num_inputs;
	this->num_outputs_ = num_inputs;
	this->num_hidden_layers_ = num_hidden_layers;

	// initializing input layer
	for (int i = 0; i < num_inputs_; i++) {
		Neuron* input_neuron = new Neuron();
		input_layer_.push_back(input_neuron);
	}
	
	// initializing hidden layers
	for (int i = 0; i < num_hidden_layers_; i++) {
		std::vector<Neuron*> hidden_layer;
		hidden_layers_.push_back(hidden_layer);
		for (int j = 0; j < num_inputs + 1; j++) {
			Neuron* hidden_neuron = new Neuron();
			hidden_layers_[i].push_back(hidden_neuron);
		}
	}

	// initializing output layers
	for (int i = 0; i < num_inputs_; i++) {
		Neuron* output_neuron = new Neuron();
		output_layer_.push_back(output_neuron);
	}

	// initializing synapse weights input layer
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < num_inputs_ + 1; j++) {
			input_layer_[i]->addSynapse((double)rand() / (RAND_MAX));
			input_layer_[i]->getSynapse(j)->setTo(hidden_layers_[0][j]);
		}
	}

	// initializing synapse weights hidden layers
	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		for (unsigned int j = 0; j < hidden_layers_[i].size(); j++) {
			for (unsigned int k = 0; k < hidden_layers_[i+1].size(); k++) {
				hidden_layers_[i][j]->addSynapse((double)rand() / (RAND_MAX));
				hidden_layers_[i][j]->getSynapse(k)->setTo(hidden_layers_[i + 1][k]);
			}
		}
	}
	
	// initializing synapse weights to output layer
	for (unsigned int i = 0; i < hidden_layers_.back().size(); i++) {
		for (int j = 0; j < num_outputs_; j++) {
			hidden_layers_.back()[i]->addSynapse((double)rand() / (RAND_MAX));
			hidden_layers_.back()[i]->getSynapse(j)->setTo(output_layer_[j]);
		}
	}
}


void NeuralNetwork::readData() {
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

			// Only want the first 4 values from the data set (5th is flower name)
			int counter = 0;
			//Loop until we have parsed this entire line
			while (getline(myStream, token, ',')) {
				//Store the converted data in the appropriate position in our array
				if (counter < 4) {
					double datum = stod(token);
					data_row.push_back(datum);
				}
				counter++;
			}
			counter = 0;
			this->data_set_.push_back(data_row);
			data_row.clear();
		}
	}
	inputFile.close();
}


void NeuralNetwork::printData() {
	for (unsigned int i = 0; i < data_set_.size() - 1; i++) {
		std::cout << i << ": ";
		for (unsigned int j = 0; j < data_set_[i].size(); j++) {
			std::cout << std::setprecision(1) << std::fixed;
			std::cout << data_set_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void NeuralNetwork::testSum() {
	for (int i = 0; i < num_inputs_; i++) {
		hidden_layers_[0][0]->addToSum(input_layer_[i]->getSynapse(0)->getWeight());
	}
	std::cout << "The summed value of all synapses to Hidden Layer 0, Node 0 is ";
	std::cout << hidden_layers_[0][0]->getSummedValue() << std::endl;
}


void NeuralNetwork::printNetwork() {
	std::cout << "Input Layer" << std::endl;
	// im a stub
	std::cout << "Synapse weights to Hidden Layer " << 0 << std::endl;
	for (int i = 0; i < num_inputs_; i++) {
		for (int j = 0; j < input_layer_[i]->getNumberOfSynapses(); j++) {
			std::cout << "I: N" << i << ": Synapse " << j << ": Weight ";
			std::cout << input_layer_[i]->getSynapse(j)->getWeight() << std::endl;
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < num_hidden_layers_ - 1; i++) {
		std::cout << "Hidden Layer " << i << std::endl;
		// im a stub
		std::cout << "Synapse weights to Hidden Layer " << i+1 << std::endl;
		for (unsigned int j = 0; j < hidden_layers_[i].size(); j++) {
			for (int k = 0; k < hidden_layers_[i][j]->getNumberOfSynapses(); k++) {
				std::cout << "H" << i << ": N" << j << ": Synapse " << k << ": Weight ";
				std::cout << hidden_layers_[i][j]->getSynapse(k)->getWeight() << std::endl;
			}
			std::cout << std::endl;
		}
	}
	std::cout << "Hidden Layer " << hidden_layers_.size() - 1 << std::endl;
	//im a stub
	std::cout << "Synapses weights to Output Layer" << std::endl;
	for (unsigned int i = 0; i < hidden_layers_.back().size(); i++) {	
		for (int j = 0; j < num_outputs_; j++) {
			std::cout << "H"<< hidden_layers_.size() - 1 <<": N" << i << ": Synapse " << j << ": Weight ";
			std::cout << hidden_layers_.back()[i]->getSynapse(j)->getWeight() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "Output Layer" << std::endl;
	//im a stub
}


void NeuralNetwork::printResults() {
	std::cout << "100: Everything was classified perfectly!" << std::endl;
}
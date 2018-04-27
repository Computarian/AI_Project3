#include "Neuron.hpp"



Neuron::Neuron(){
	this->number_of_synapses_ = 0;
}


double Neuron::getSummedValue() {
	return this->summed_value_;
}


Synapse* Neuron::getSynapse(int i) {
	return synapses_[i];
}


void Neuron::addSynapse(double weight) {
	Synapse* new_synapse = new Synapse(weight);
	synapses_.push_back(new_synapse);
	this->number_of_synapses_++;
}


void Neuron::addToSum(double value) {
	this->summed_value_ += value;
}


int Neuron::getNumberOfSynapses() {
	return this->number_of_synapses_;
}
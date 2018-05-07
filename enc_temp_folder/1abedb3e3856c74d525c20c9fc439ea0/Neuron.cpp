#include "Neuron.hpp"



Neuron::Neuron(){
	this->number_of_synapses_ = 0;
	this->summed_value_ = 0.0;
	this->computed_value_ = 0.0;
	this->output_value_ = 0.0;
}


double Neuron::getSummedValue() {
	return this->summed_value_;
}


double Neuron::getComputedValue() {
	return this->computed_value_;
}


double Neuron::getOutputValue() {
	return this->output_value_;
}


Synapse* Neuron::getSynapse(int i) {
	return synapses_[i];
}


void Neuron::addSynapse(double weight) {
	Synapse* new_synapse = new Synapse(weight);
	synapses_.push_back(new_synapse);
	this->number_of_synapses_++;
}


void Neuron::setOutputValue(double weight) {
	this->output_value_ = weight;
}


void Neuron::addToSum(double value) {
	this->summed_value_ += value;
}


int Neuron::getNumberOfSynapses() {
	return this->number_of_synapses_;
}
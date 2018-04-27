#include "Synapse.hpp"


Synapse::Synapse(double weight){
	this->weight_ = weight;
}


void Synapse::setWeight(double weight) {
	this->weight_ = weight;
}


double Synapse::getWeight() {
	return this->weight_;
}


void Synapse::setTo(Neuron* to) {
	this->to_ = to;
}



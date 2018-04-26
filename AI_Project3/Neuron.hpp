#ifndef NEURON_HPP
#define NEURON_HPP


#include "Synapse.hpp"
#include <vector>


class Neuron {

public:
	Neuron();
	Neuron(int numSynapses);
	double getSummedValue();
	double getComputedValue();
	Synapse* getSynapse(int i);
	void addSynapse(double weight);

	void setSummedValue(double weight);

	void addToSum(double value);
	double tangentActivationFunction();
	double sigmoidActivationFunction();
	void computeValue();
	double classify();

	double calculateDerivative();
	double sigmoidDerivative();
	double tangentDerivative();
	int numberOfSynapses();

private:
	double summed_value_ = 0.0;
	double computed_value_ = 0.0;
	std::vector<Synapse*> synapses_;

};

#endif //NEURON_HPP
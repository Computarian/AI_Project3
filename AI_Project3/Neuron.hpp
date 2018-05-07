#ifndef NEURON_HPP
#define NEURON_HPP


#include "Synapse.hpp"
#include <vector>
#include <time.h>

class Neuron {

public:
	Neuron();
	Neuron(int numSynapses);
	double getSummedValue();
	double getComputedValue();
	double getOutputValue();
	Synapse* getSynapse(int i);
	void addSynapse(double weight);

	void setSummedValue(double weight);
	void setOutputValue(double weight);

	void addToSum(double value);
	double tangentActivationFunction();
	double sigmoidActivationFunction();
	void computeValue();
	double classify();

	double calculateDerivative();
	double sigmoidDerivative();
	double tangentDerivative();
	int getNumberOfSynapses();

private:
	double summed_value_;
	double computed_value_;
	double output_value_;
	std::vector<Synapse*> synapses_;
	int number_of_synapses_;
};

#endif //NEURON_HPP
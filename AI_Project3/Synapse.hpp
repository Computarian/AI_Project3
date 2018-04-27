#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

class Neuron;

class Synapse {

public:
	Synapse(double weight);
	void setWeight(double weight);
	double getWeight();
	void setTo(Neuron* to);
private:
	double weight_;
	Neuron* to_;
};

#endif //SYNAPSE_HPP
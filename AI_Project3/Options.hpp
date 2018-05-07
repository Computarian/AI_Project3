#ifndef OPTIONS_HPP
#define OPTIONS_HPP

class Options {
public:
	// number of input and hidden neurons
	static const int num_inputs = 4;
	static const int num_hidden = 5;
	// number of hidden layers
	static const int num_hidden_layers = 2;

	// enables debug print statements
	static const bool debug = 1;
};

#endif //OPTIONS_HPP
#ifndef OPTIONS_HPP
#define OPTIONS_HPP

class Options {
public:
	// number of input and hidden neurons
	static const int num_inputs = 4;
	static const int num_hidden = 5;
	// number of hidden layers
	static const int num_hidden_layers = 1;
	static const int epochs = 40;
	static const int test_net = 10;
	// enables debug print statements
	static const bool debug = 0;
};

#endif //OPTIONS_HPP
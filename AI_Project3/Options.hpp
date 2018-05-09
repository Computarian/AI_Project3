#ifndef OPTIONS_HPP
#define OPTIONS_HPP

class Options {
public:
	// number of neurons
	static const int num_inputs = 4;
	static const int num_hidden = 5;
	// number of hidden layers
	static const int num_hidden_layers = 2;

	// data training range
	static const int epochs = 40;
	// data testing range
	static const int test_net = 10;
	// number of times neural networks have full train/test cycles
	static const int cycles = 1;

	// enables debug print statements
	static const bool debug = 0;
	static const bool print_guesses = 1;
};

#endif //OPTIONS_HPP
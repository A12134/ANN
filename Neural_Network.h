#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#include "INPUT_NEURON.h"
#include "HIDDEN_NEURON.h"
#include "OUTPUT_NEURON.h"
#include "NEURON_EDGE.h"
#include <vector>

class Neural_Network
{
private:
	std::vector<NEURON*> m_Input_Neurons;
	std::vector<NEURON*> m_Output_Neurons;

	std::vector<std::vector<NEURON*>> m_hiddenLayer;

	double m_learningRate;

public:
	/* @param: (int)input neuron numbers
			   (vector<int>) hidden layers neuron numbers
			   (int)output neuron numbers
	*/
	Neural_Network(int input, std::vector<int> hidden, int output);
	~Neural_Network();

	void feedForward(std::vector<double> inputs);

	std::vector<double> getNetworkOutputVector();

	void setNeuralNetworkLearningRate(double val) { this->m_learningRate = val; }

	void training(std::vector<std::vector<double>> trainingSet, std::vector<std::vector<double>> sampleOutput);

private:
	// used for training the neural network
	void backPropagation(std::vector<double> sampleOutput);

	void linkTwoLayer(std::vector<NEURON*>* layer1, std::vector<NEURON*>* layer2);
	
	// compute the single edge weight change for target, actual output, and input neuron value
	double UTILS_deltaRule(NEURON_EDGE* edge);
};
#endif


#ifndef ACTIVATION_LIBRARY_H
#define ACTIVATION_LIBRARY_H

enum class ACTIVATION 
{
	A_SIGMOID,
	A_STEP,
	A_TanH,
	A_ReLu,
	A_Linear
};

class ActivationLibrary
{
public:
	// a threshold value used for step function
	static double threshold;

	// constant values used for linear function
	static double linearConstantMultply;
	static double linearConstantAddition;

	static float learningRate;

	// activation key -- used to determine which activation function to use for the neural network
	static ACTIVATION key;

	ActivationLibrary();
	~ActivationLibrary();

	static double activationFunction(double value);

	static double derivFunction(double value);

private:

	// never use step function in regular neural network, genetic neural network only
	static double stepFunction(double value);

	static double linearFunction(double value);
	static double derivLinear(double value);

	static double sigmoidFunction(double value);
	static double derivSigmoid(double value);

	static double tanhFunction(double value);
	static double derivTanh(double value);

	static double reluFunction(double value);
	static double derivRelu(double value);
};
#endif


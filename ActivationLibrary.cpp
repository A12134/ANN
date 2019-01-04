#include "ActivationLibrary.h"
#include <cmath>

ACTIVATION ActivationLibrary::key = ACTIVATION::A_SIGMOID;
double ActivationLibrary::linearConstantAddition = 0;
double ActivationLibrary::linearConstantMultply = 1;
double ActivationLibrary::threshold = 0.5f;
float ActivationLibrary::learningRate = 0.5f;

ActivationLibrary::ActivationLibrary()
{
}


ActivationLibrary::~ActivationLibrary()
{
}

double ActivationLibrary::activationFunction(double value)
{
	switch (key)
	{
	case ACTIVATION::A_SIGMOID:
		return sigmoidFunction(value);
	case ACTIVATION::A_STEP:
		return stepFunction(value);
	case ACTIVATION::A_TanH:
		return tanhFunction(value);
	case ACTIVATION::A_ReLu:
		return reluFunction(value);
	case ACTIVATION::A_Linear:
		return linearFunction(value);
	default:
		break;
	}
}

double ActivationLibrary::derivFunction(double value)
{
	switch (key)
	{
	case ACTIVATION::A_SIGMOID:
		return derivSigmoid(value);
	case ACTIVATION::A_STEP:
		return stepFunction(value);
	case ACTIVATION::A_TanH:
		return derivTanh(value);
	case ACTIVATION::A_ReLu:
		return derivRelu(value);
	case ACTIVATION::A_Linear:
		return derivLinear(value);
	default:
		break;
	}
}

double ActivationLibrary::stepFunction(double value)
{
	return value > threshold ? 1 : 0;
}


double ActivationLibrary::linearFunction(double value)
{
	return value*linearConstantMultply + linearConstantAddition;
}

double ActivationLibrary::derivLinear(double value)
{
	return linearConstantMultply;
}

double ActivationLibrary::sigmoidFunction(double value)
{
	return 1/(1 + std::exp(-value));
}

double ActivationLibrary::derivSigmoid(double value)
{
	return value*(1-value);
}

double ActivationLibrary::tanhFunction(double value)
{
	return std::tanh(value);
}

double ActivationLibrary::derivTanh(double value)
{
	return 1- std::tanh(value)*std::tanh(value);
}

double ActivationLibrary::reluFunction(double value)
{
	return value > 0? value : 0;
}

double ActivationLibrary::derivRelu(double value)
{
	return value > 0 ? value : 0;
}

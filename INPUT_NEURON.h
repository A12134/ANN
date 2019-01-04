#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H
#include "NEURON.h"

class INPUT_NEURON :
	public NEURON
{
protected:
	virtual double ActivateFunction(double val) override;

	// empty function
	virtual void chainRule() override;

	// empty
	virtual void chainRule(double tmp) override;

public:
	INPUT_NEURON();
	~INPUT_NEURON();
};

#endif


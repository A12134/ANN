#ifndef OUTPUT_NEURON_H
#define OUTPUT_NEURON_H
#include "NEURON.h"
class OUTPUT_NEURON :
	public NEURON
{
protected:
	// empty function
	virtual void chainRule() override;

public:
	virtual void chainRule(double target) override;

public:
	OUTPUT_NEURON();
	~OUTPUT_NEURON();
};
#endif


#ifndef HIDDEN_NEURON_H
#define HIDDEN_NEURON_h
#include "NEURON.h"
class HIDDEN_NEURON :
	public NEURON
{
public:
	virtual void chainRule() override;

protected:
	// empty
	virtual void chainRule(double target) override;
public:
	HIDDEN_NEURON();
	~HIDDEN_NEURON();
};
#endif


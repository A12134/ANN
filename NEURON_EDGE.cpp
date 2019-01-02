#include "NEURON_EDGE.h"



NEURON_EDGE::NEURON_EDGE(NEURON * In, NEURON * Out)
{
	this->m_In = In;
	this->m_Out = Out;
	this->weight = 0.0f;
	this->deltaWeight = 0.0f;
	this->trainingCount = 0;
}

NEURON_EDGE::~NEURON_EDGE()
{
	this->m_In = nullptr;
	this->m_Out = nullptr;
}

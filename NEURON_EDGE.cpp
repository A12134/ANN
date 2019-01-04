#include "NEURON_EDGE.h"
#include <cstdlib>


NEURON_EDGE::NEURON_EDGE(NEURON * In, NEURON * Out)
{
	this->m_In = In;
	this->m_Out = Out;
	this->weight = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/2) - 1;
	this->deltaWeight = 0.0f;
	this->trainingCount = 0;
}

NEURON_EDGE::~NEURON_EDGE()
{
	this->m_In = nullptr;
	this->m_Out = nullptr;
}

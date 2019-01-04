#include "OUTPUT_NEURON.h"
#include "NEURON_EDGE.h"
#include "ActivationLibrary.h"

void OUTPUT_NEURON::chainRule()
{
}

void OUTPUT_NEURON::chainRule(double target)
{
	this->hiddenValue = ActivationLibrary::derivFunction(this->value)*(this->value - target);
	for (unsigned int i = 0; i < this->m_IncomingEdges.size(); i++)
	{

		NEURON_EDGE* edge = m_IncomingEdges.at(i);
		double preValue = edge->getInputNeuron()->getOutValue();
		edge->increaseTrainingCount();
		edge->setDeltaWeight(edge->getDeltaWeight() - ActivationLibrary::learningRate * preValue * this->hiddenValue);
	}
}

OUTPUT_NEURON::OUTPUT_NEURON()
{
}


OUTPUT_NEURON::~OUTPUT_NEURON()
{
}

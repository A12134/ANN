#include "HIDDEN_NEURON.h"
#include "NEURON_EDGE.h"
#include "ActivationLibrary.h"


void HIDDEN_NEURON::chainRule()
{
	double tmpValue = 0;

	for (unsigned int i = 0; i < this->m_OutgoingEdges.size(); i++)
	{
		NEURON_EDGE* edge = m_OutgoingEdges.at(i);
		tmpValue += edge->getOutputNeuron()->getHiddenValue() * edge->getWeight();
	}

	for (unsigned int i = 0; i < this->m_IncomingEdges.size(); i++)
	{
		double preNeuronOutPut = m_IncomingEdges.at(i)->getInputNeuron()->getOutValue();
		NEURON_EDGE* edge = m_IncomingEdges.at(i);

		this->hiddenValue = ActivationLibrary::derivFunction(this->value)*tmpValue;
		edge->increaseTrainingCount();
		edge->setDeltaWeight(edge->getDeltaWeight() - ActivationLibrary::learningRate * preNeuronOutPut*this->hiddenValue);
	}
}

void HIDDEN_NEURON::chainRule(double target)
{
}

HIDDEN_NEURON::HIDDEN_NEURON()
{
}


HIDDEN_NEURON::~HIDDEN_NEURON()
{
}

#include "NEURON.h"
#include "NEURON_EDGE.h"
#include "ActivationLibrary.h"


double NEURON::ActivateFunction(double val)
{
	return ActivationLibrary::activationFunction(val);
}

void NEURON::chainRule()
{
}

void NEURON::chainRule(double target)
{
}

NEURON::NEURON()
{
	this->value = 0.0f;
	this->bias = 0.0f;
}


NEURON::~NEURON()
{
	for (unsigned int i = 0; i < m_OutgoingEdges.size(); i++)
	{
		this->m_OutgoingEdges.at(i) = nullptr;
	}

	for (unsigned int i = 0; i < m_IncomingEdges.size(); i++)
	{
		delete this->m_IncomingEdges.at(i);
		this->m_IncomingEdges.at(i) = nullptr;
	}
	m_OutgoingEdges.clear();
	m_IncomingEdges.clear();
	std::vector<NEURON_EDGE*>().swap(m_OutgoingEdges);
	std::vector<NEURON_EDGE*>().swap(m_IncomingEdges);
}

void NEURON::addIncomingEdge(NEURON_EDGE* edge)
{
	this->m_IncomingEdges.push_back(edge);
}

void NEURON::addOutgoingEdge(NEURON_EDGE* edge)
{
	this->m_OutgoingEdges.push_back(edge);
}

void NEURON::setInValue(double val)
{
	this->value = val;
}

void NEURON::getInputValue()
{
	double input = 0;
	for (unsigned int i = 0; i < m_IncomingEdges.size(); i++)
	{
		NEURON_EDGE* tmpEdge = m_IncomingEdges.at(i);
		input += tmpEdge->getWeight() * tmpEdge->getInputNeuron()->getOutValue();
		tmpEdge = nullptr;
	}
	this->value = ActivateFunction(input + bias);
}

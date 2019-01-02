#ifndef NEURON_H
#define NEURON_H
#include <vector>

/*
	Basic neuron node
	Each neuron contains two main properties, edges that connect to other neuron, and the activation function
*/

class NEURON_EDGE;

class NEURON
{
protected:
	double value;
	double bias;
	double deltaValue;
	double desireValue;

	std::vector<NEURON_EDGE*> m_IncomingEdges;
	std::vector<NEURON_EDGE*> m_OutgoingEdges;

protected:
	virtual double ActivateFunction(double val);

public:
	NEURON();
	~NEURON();
	void addIncomingEdge(NEURON_EDGE* edge);
	void addOutgoingEdge(NEURON_EDGE* edge);

	std::vector<NEURON_EDGE*>* getIncomingEdges() { return &m_IncomingEdges; }

	std::vector<NEURON_EDGE*>* getOutgoingEdges() { return &m_OutgoingEdges; }

	void setDeltaValue(double val) { this->deltaValue = val; }

	double getDeltaValue() { return this->deltaValue; }

	void setBias(double value) { this->bias = value; }

	double getOutValue() { return value; }

	void setdesireValue(double val) { this->desireValue = val; }

	double getdesireValue() { return this->desireValue; }
	
	// for input layer only
	void setInValue(double val);

	// for all other layers
	void getInputValue();
};

#endif


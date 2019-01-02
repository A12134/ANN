#ifndef NEURON_EDGE_H
#define NEURON_EDGE_H
/*
	The neuron edge contains the weight of the edge and NEURONs that are connected by the edge
*/
class NEURON;

class NEURON_EDGE
{
protected:
	NEURON * m_In;
	NEURON * m_Out;
	double weight;
	double deltaWeight;
	int trainingCount;

public:
	NEURON_EDGE(NEURON* In, NEURON* Out);
	~NEURON_EDGE();

	double getWeight() { return weight; }
	NEURON* getInputNeuron() { return m_In; }
	NEURON* getOutputNeuron() { return m_Out; }

	void increaseTrainingCount() { trainingCount += 1; }

	void setDeltaWeight(double val) { this->deltaWeight = val; }
	double getDeltaWeight() { return this->deltaWeight; }
	void updateWeight() { this->weight -= this->deltaWeight / trainingCount; trainingCount = 0; this->deltaWeight = 0; }


};

#endif


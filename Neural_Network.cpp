#include "Neural_Network.h"
#include <ctime>
#include <cstdlib>


Neural_Network::Neural_Network(int input, std::vector<int> hidden, int output)
{
	srand(std::time(NULL));
	// initialize neuron layers -- input layer
	for (int i = 0; i < input; i++)
	{
		m_Input_Neurons.push_back(new NEURON());
	}


	// initialize neuron layers -- hidden layers
	for (unsigned int i = 0; i < hidden.size(); i++)
	{
		int neuronNum = hidden.at(i);
		m_hiddenLayer.push_back(std::vector<NEURON*>());
		for (unsigned int j = 0; j < neuronNum; j++)
		{
			m_hiddenLayer.at(m_hiddenLayer.size() - 1).push_back(new NEURON());
		}
	}

	// initialize neuron layer -- output layer
	for (unsigned int i = 0; i < output; i++)
	{
		m_Output_Neurons.push_back(new NEURON());
	}

	// link hidden layers with edges
	for (unsigned int i = 0; i < m_hiddenLayer.size()-1; i++)
	{
		std::vector<NEURON*>* currentLayer = &m_hiddenLayer.at(i);
		std::vector<NEURON*>* nextLayer = &m_hiddenLayer.at(i + 1);
		linkTwoLayer(currentLayer, nextLayer);
		currentLayer = nullptr;
		nextLayer = nullptr;
	}

	// lint input layer with output layer if there is no hidden layer
	if (m_hiddenLayer.size() == 0)
	{
		// link input and output
		linkTwoLayer(&m_Input_Neurons, &m_Output_Neurons);
	}
	else
	{
		// link input layer with hiddenLayer
		linkTwoLayer(&m_Input_Neurons, &(m_hiddenLayer.at(0)));

		// link output layer with hiddenLayer
		linkTwoLayer(&(m_hiddenLayer.at(m_hiddenLayer.size() - 1)), &m_Output_Neurons);
	}
}

Neural_Network::~Neural_Network()
{
	for (unsigned int i = 0; i < m_Input_Neurons.size(); i++)
	{
		delete m_Input_Neurons.at(i);
		m_Input_Neurons.at(i) = nullptr;
	}
	m_Input_Neurons.clear();
	std::vector<NEURON*>().swap(m_Input_Neurons);

	for (unsigned int i = 0; i < m_hiddenLayer.size(); i++)
	{
		for (unsigned int j = 0; j < m_hiddenLayer.at(i).size(); j++)
		{
			delete m_hiddenLayer.at(i).at(j);
			m_hiddenLayer.at(i).at(j) = nullptr;
		}
		m_hiddenLayer.at(i).clear();
		std::vector<NEURON*>().swap(m_hiddenLayer.at(i));
	}
	m_hiddenLayer.clear();
	std::vector<std::vector<NEURON*>>().swap(m_hiddenLayer);

	for (unsigned int i = 0; i < m_Output_Neurons.size(); i++)
	{
		delete m_Output_Neurons.at(i);
		m_Output_Neurons.at(i) = nullptr;
	}
	m_Output_Neurons.clear();
	std::vector<NEURON*>().swap(m_Output_Neurons);
}

void Neural_Network::linkTwoLayer(std::vector<NEURON*>* layer1, std::vector<NEURON*>* layer2)
{
	for (unsigned int i = 0; i < layer1->size(); i++)
	{
		for (unsigned int j = 0; j < layer2->size(); j++)
		{
			NEURON_EDGE* tmpEdge = new NEURON_EDGE(layer1->at(i), layer2->at(j));
			layer1->at(i)->addOutgoingEdge(tmpEdge);
			layer2->at(j)->addIncomingEdge(tmpEdge);
			tmpEdge = nullptr;
		}
	}
}

double Neural_Network::UTILS_deltaRule(NEURON_EDGE* edge)
{
	NEURON* out = edge->getOutputNeuron();
	NEURON* in = edge->getInputNeuron();
	double target = out->getdesireValue();
	double outVal = out->getOutValue();
	double inVal = in->getOutValue();

	// used for previous layer
	out->setDeltaValue(-(target - outVal)*outVal*(1 - outVal));
	
	// deltaRule
	edge->setDeltaWeight(this->m_learningRate*out->getDeltaValue());

	in->setdesireValue(in->getdesireValue() + out->getDeltaValue());

	edge->increaseTrainingCount();

	out = nullptr;
	in = nullptr;
	return 0.0f;
}

void Neural_Network::feedForward(std::vector<double> inputs) 
{
	// feed the input to input layer
	for (unsigned int i = 0; i < m_Input_Neurons.size(); i++)
	{
		if (i >= inputs.size()) 
		{
			m_Input_Neurons.at(i)->setInValue(0);
		}
		else 
		{
			m_Input_Neurons.at(i)->setInValue(inputs.at(i));
		}
	}

	// feedforward into hidden Layer
	for (unsigned int i = 0; i < m_hiddenLayer.size(); i++)
	{
		std::vector<NEURON*>* currentLayer = &m_hiddenLayer.at(i);
		for (unsigned int j = 0; j < currentLayer->size(); j++)
		{
			NEURON* tmpNeuron = currentLayer->at(j);
			tmpNeuron->getInputValue();
			tmpNeuron = nullptr;
		}
		currentLayer = nullptr;
	}

	// feedforward into the output layer
	for (unsigned int i = 0; i < m_Output_Neurons.size(); i++)
	{
		m_Output_Neurons.at(i)->getInputValue();
	}
}

std::vector<double> Neural_Network::getNetworkOutputVector()
{
	std::vector<double> output;
	for (unsigned int i = 0; i < m_Output_Neurons.size(); i++)
	{
		output.push_back(m_Output_Neurons.at(i)->getOutValue());
	}

	return output;
}

void Neural_Network::training(std::vector<std::vector<double>> trainingSet, std::vector<std::vector<double>> sampleOutput)
{
	// feed training data into network
	for (unsigned int i = 0; i < trainingSet.size(); i++)
	{
		this->feedForward(trainingSet.at(i));
		this->backPropagation(sampleOutput.at(i));
	}

	// update weight after single training iteration
	for (unsigned int i = 0; i < m_Input_Neurons.size(); i++)
	{
		for (unsigned int j = 0; j < m_Input_Neurons.at(i)->getOutgoingEdges()->size(); j++)
		{
			m_Input_Neurons.at(i)->getOutgoingEdges()->at(j)->updateWeight();
		}
	}

	for (unsigned int i = 0; i < m_hiddenLayer.size(); i++)
	{
		std::vector<NEURON*>* layer = &m_hiddenLayer.at(i);
		for (unsigned int j = 0; j < layer->size(); j++)
		{
			for (unsigned int z = 0; z < layer->at(z)->getOutgoingEdges()->size(); z++)
			{
				layer->at(j)->getOutgoingEdges()->at(z)->updateWeight();
			}
		}
	}
}

void Neural_Network::backPropagation(std::vector<double> sampleOutput)
{

	

	// back propagation start from output layer
	for (unsigned int i = 0; i < m_Output_Neurons.size(); i++)
	{
		NEURON* neuron = m_Output_Neurons.at(i);
		neuron->setdesireValue(sampleOutput.at(i));
		for (unsigned int j = 0; j < neuron->getIncomingEdges()->size(); j++)
		{
			// set output neuron's desire output
			UTILS_deltaRule(neuron->getIncomingEdges()->at(j));
		}
		neuron = nullptr;
	}

	// go through hidden layer
	for (unsigned int i = 0; i < m_hiddenLayer.size(); i++)
	{
		for (unsigned int j = 0; j < m_hiddenLayer.at(i).size(); j++)
		{
			NEURON* neuron = m_hiddenLayer.at(i).at(j);
			for (unsigned int z = 0; z < neuron->getIncomingEdges()->size(); z++)
			{
				UTILS_deltaRule(neuron->getIncomingEdges()->at(z));
			}
			neuron = nullptr;
		}
	}
}

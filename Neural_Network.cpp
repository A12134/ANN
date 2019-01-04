#include "Neural_Network.h"
#include "NEURON.h"
#include <ctime>
#include <cstdlib>


Neural_Network::Neural_Network(int input, std::vector<int> hidden, int output)
{
	m_learningRate = 1.0f;
	// initialize neuron layers -- input layer
	for (int i = 0; i < input; i++)
	{
		m_Input_Neurons.push_back(new INPUT_NEURON());
	}


	// initialize neuron layers -- hidden layers
	for (unsigned int i = 0; i < hidden.size(); i++)
	{
		int neuronNum = hidden.at(i);
		m_hiddenLayer.push_back(std::vector<NEURON*>());
		for (unsigned int j = 0; j < neuronNum; j++)
		{
			m_hiddenLayer.at(m_hiddenLayer.size() - 1).push_back(new HIDDEN_NEURON());
		}
	}

	// initialize neuron layer -- output layer
	for (unsigned int i = 0; i < output; i++)
	{
		m_Output_Neurons.push_back(new OUTPUT_NEURON());
	}

	// link hidden layers with edges

	if (hidden.size() > 1)
	{
		int sizeOfHiddenLayer = m_hiddenLayer.size() - 1;

		for (unsigned int i = 0; i < sizeOfHiddenLayer; i++)
		{
			std::vector<NEURON*>* currentLayer = &m_hiddenLayer.at(i);
			std::vector<NEURON*>* nextLayer = &m_hiddenLayer.at(i + 1);
			linkTwoLayer(currentLayer, nextLayer);
			currentLayer = nullptr;
			nextLayer = nullptr;
		}
	}
	

	// lint input layer with output layer if there is no hidden layer
	if (hidden.size() == 0)
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

// link two neural layers with edges
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

// returns the result of neural network
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
			for (unsigned int z = 0; z < layer->at(j)->getOutgoingEdges()->size(); z++)
			{
				layer->at(j)->getOutgoingEdges()->at(z)->updateWeight();
			}
		}
	}

}

void Neural_Network::backPropagation(std::vector<double> sampleOutput)
{
	// start chain rule for each output neuron
	for (unsigned int i = 0; i < this->m_Output_Neurons.size(); i++)
	{
		OUTPUT_NEURON* neuron = (OUTPUT_NEURON*)this->m_Output_Neurons.at(i);
		neuron->chainRule(sampleOutput.at(i));
	}

	// start chain rule for each hidden neuron
	for (unsigned int i = 0; i < this->m_hiddenLayer.size(); i++)
	{
		for (unsigned int j = 0; j < this->m_hiddenLayer.at(i).size(); j++)
		{
			HIDDEN_NEURON* neuron = (HIDDEN_NEURON*)this->m_hiddenLayer.at(i).at(j);
			neuron->chainRule();
		}
	}
}

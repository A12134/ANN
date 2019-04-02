#include "Neural_Network.h"
#include <iostream>
#include <ctime>
#include <cstdlib>



void main() 
{
	// setup hidden neuron layer
	std::vector<int> hiddenLayerNeurons;
	hiddenLayerNeurons.push_back(2); // add one layer with 2 neurons

	// create a neural network with 1 input and 1 output
	Neural_Network* brain_cancer = new Neural_Network(1, hiddenLayerNeurons, 1);

	std::cout << "training network, please wait..." << std::endl;

	int trainingIteration = 1000;
	// training process
	for (unsigned int i = 0; i < trainingIteration; i++)
	{
		srand(unsigned(time(0)));
		std::vector<std::vector<double>> trainingSet;
		std::vector<std::vector<double>> answers;
		std::cout << "training network, please wait...   " << "iteration: " << i  << "/" << trainingIteration << std::endl;
		// auto input and answer generate
		for (unsigned int j = 0; j < 100; j++)
		{
			
			std::vector<double> tmp;
			tmp.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			trainingSet.push_back(tmp);

			std::vector<double> answer;
			if (tmp.at(0) > 0.5) 
			{
				answer.push_back(1);
			}
			else 
			{
				answer.push_back(0);
			}

			answers.push_back(answer);
		}

		brain_cancer->training(trainingSet, answers);
	}

	// testing accuracy
	int count = 0;
	int testNum = 10000;

	for (unsigned int i = 0; i < testNum; i++)
	{
		double num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		std::vector<double> input;
		input.push_back(num);

		brain_cancer->feedForward(input);

		if (num > 0.5f) 
		{
			std::vector<double> answer;
			answer = brain_cancer->getNetworkOutputVector();

			if (answer.at(0) > 0.5f) 
			{
				count += 1;
			}
		}
		else 
		{
			std::vector<double> answer;
			answer = brain_cancer->getNetworkOutputVector();

			if (answer.at(0) <= 0.5f)
			{
				count += 1;
			}
		}
	}

	std::cout << "total test cases: ";
	std::cout << testNum;
	std::cout << ". " << std::endl;
	std::cout << "Correct: ";
	std::cout << count;
	std::cout << std::endl;

	std::cout << "Accuracy: ";
	std::cout << ((float)count / testNum)*100;
	std::cout << "%" << std::endl;

	system("PAUSE");

	delete brain_cancer;

	brain_cancer = nullptr;
	

	
}


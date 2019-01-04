#include "Neural_Network.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

std::vector<double> bin(int num, int maxLength)
{
	std::vector<double> binary;
	int dec = num;

	while (dec > 0)
	{
		binary.push_back(dec % 2);
		dec = dec / 2;
	}

	std::vector<double> retVal;

	for (unsigned int i = 0; i < maxLength - binary.size(); i++)
	{
		retVal.push_back(0);
	}

	for (unsigned int i = 0; i < binary.size(); i++)
	{
		retVal.push_back(binary.at(i));
	}

	return retVal;
}

void main() 
{
	std::vector<int> hiddenLayerNeurons;
	hiddenLayerNeurons.push_back(3);

	Neural_Network* brain_cancer = new Neural_Network(1, hiddenLayerNeurons, 1);

	for (unsigned int i = 0; i < 10000; i++)
	{
		srand(unsigned(time(0)));
		std::vector<std::vector<double>> trainingSet;
		std::vector<std::vector<double>> answers;

		for (unsigned int i = 0; i < 10; i++)
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

	int count = 0;

	for (unsigned int i = 0; i < 100; i++)
	{
		double num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		std::vector<double> input;
		input.push_back(num);

		brain_cancer->feedForward(input);

		if (num > 0.5f) 
		{
			std::vector<double> answer;
			answer = brain_cancer->getNetworkOutputVector();

			std::cout << "input: ";
			std::cout << num;
			std::cout << std::endl;

			std::cout << "Answer: ";
			std::cout << answer.at(0);
			std::cout << std::endl;

			if (answer.at(0) > 0.5f) 
			{
				count += 1;
			}
		}
		else 
		{
			std::vector<double> answer;
			answer = brain_cancer->getNetworkOutputVector();

			std::cout << "input: ";
			std::cout << num;
			std::cout << std::endl;

			std::cout << "Answers: ";
			std::cout << answer.at(0);
			std::cout << std::endl;

			if (answer.at(0) <= 0.5f)
			{
				count += 1;
			}
		}
	}

	std::cout << "Accuracy: ";
	std::cout << ((float)count / 100);
	std::cout << "%" << std::endl;

	/*
	std::vector<int> hiddenLayerNeurons;
	hiddenLayerNeurons.push_back(8);
	Neural_Network* brain_cancer = new Neural_Network(16, hiddenLayerNeurons, 12);
	

	// training step, training 50 times

	for (unsigned int count = 0; count < 1000; count++)
	{
		srand(unsigned(time(0)));
		std::vector<std::vector<double>> trainingSet;
		std::vector<std::vector<double>> sampleOutput;

		for (unsigned int i = 0; i < 100; i++)
		{
			int num_1 = (rand() % 255);
			int num_2 = (rand() % 255);
			std::vector<double> num1 = bin(num_1, 8);
			std::vector<double> num2 = bin(num_2, 8);

			for (unsigned int i = 0; i < 8; i++)
			{
				num1.push_back(num2.at(i));
			}

			trainingSet.push_back(num1);

			sampleOutput.push_back(bin(num_1 + num_2, 12));
		}

		brain_cancer->training(trainingSet, sampleOutput);
	}

	// accuracy test
	int totalTest = 100;
	int correctCount = 0;

	for (unsigned int i = 0; i < totalTest; i++)
	{
		int num_1 = (rand() % 1 + 256) - 1;
		int num_2 = (rand() % 1 + 256) - 1;
		std::vector<double> num1 = bin(num_1, 8);
		std::vector<double> num2 = bin(num_2, 8);

		for (unsigned int i = 0; i < 8; i++)
		{
			num1.push_back(num2.at(i));
		}

		std::vector<double> correctAns = bin(num_1 + num_2, 12);

		brain_cancer->feedForward(num1);

		std::vector<double> brainCancerAns = brain_cancer->getNetworkOutputVector();

		bool equalFlag = true;
		for (unsigned int output = 0; output < 12; output++)
		{
			std::cout << (float)brainCancerAns.at(output);
			std::cout << "_";
			if (brainCancerAns.at(output) != correctAns.at(output)) 
			{
				equalFlag = false;
				break;
			}
		}
		std::cout << "." << std::endl;

		if (equalFlag) 
		{
			correctCount += 1;
		}
	}

	std::cout << "Accuracy: ";
	std::cout << (float)(correctCount / totalTest);
	std::cout << "%" << std::endl;
	*/
	system("PAUSE");
	

	
}


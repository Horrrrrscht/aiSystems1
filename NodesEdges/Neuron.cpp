#include "Node.h"
#include <iostream>

using namespace std;

double Neuron::eta = 0.05;
double Neuron::alpha = 0.5;




Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
		cout << m_outputWeights.back().weight << endl;
	}

	m_myIndex = myIndex;
}

void Neuron::feedForward(const Layer &prevLayer) {

	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		sum +=	prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x) {

	return tanh(x/10);
}

double Neuron::transferFunctionDerivative(double x) {

	return 1.0 - x*x;
}

void Neuron::calcOutputGradients(double targetVal) {

	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {

	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::sumDOW(const Layer &nextLayer) const {

	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {

		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer) {

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
		
		double newDeltaWeight = eta
			* neuron.getOutputVal()
			* m_gradient
			+ alpha
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;

	}
}




Neuron::~Neuron()
{
}
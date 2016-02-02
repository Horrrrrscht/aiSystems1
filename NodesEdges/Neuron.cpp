#include "Node.h"
#include <iostream>

using namespace std;

double Neuron::learningRate = 0.05;
double Neuron::alpha = 0.5;




Neuron::Neuron(unsigned numOutputs, unsigned myId)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputStrengths.push_back(Connection());
		m_outputStrengths.back().strength = randomWeight();
		cout << m_outputStrengths.back().strength << endl;
	}

	m_id = myId;
}

void Neuron::feedForward(const Layer &prevLayer) {

	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		sum +=	prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputStrengths[m_id].strength;
	}

	m_ergebnis = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x) {

	return tanh(x/10);
}

double Neuron::transferFunctionDerivative(double x) {

	return 1.0 - x*x;
}

void Neuron::calcOutputGradients(double targetVal) {

	double delta = targetVal - m_ergebnis;
	m_steigung = delta * Neuron::transferFunctionDerivative(m_ergebnis);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {

	double dow = sumDOW(nextLayer);
	m_steigung = dow * Neuron::transferFunctionDerivative(m_ergebnis);
}

double Neuron::sumDOW(const Layer &nextLayer) const {

	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {

		sum += m_outputStrengths[n].strength * nextLayer[n].m_steigung;
	}

	return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer) {

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		Neuron &neuron = prevLayer[n];
		double oldDeltaStrength = neuron.m_outputStrengths[m_id].deltaStrength;
		
		double newDeltaStrength = learningRate
			* neuron.getOutputVal()
			* m_steigung
			+ alpha
			* oldDeltaStrength;

		neuron.m_outputStrengths[m_id].deltaStrength = newDeltaStrength;
		neuron.m_outputStrengths[m_id].strength += newDeltaStrength;

	}
}




Neuron::~Neuron()
{
}

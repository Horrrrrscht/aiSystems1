#include "Neuron.h"
#include <iostream>
#include "Synapse.h"

using namespace std;

double Neuron::learningRate = 0.05;
double Neuron::alpha = 0.005;




Neuron::Neuron(unsigned numOutputs, unsigned myId)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputStrengths.push_back(Synapse());
		m_outputStrengths.back().setStrength(randomStrength());
		m_outputStrengths.back().setDeltaStrength(m_outputStrengths.back().getStrength());
		//cout << m_outputStrengths.back().getStrength() << endl;
	}

	m_id = myId;
}

void Neuron::feedForward( Layer &prevLayer) {

	double summe = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		summe = (prevLayer[n].getOutputWert() *
			prevLayer[n].m_outputStrengths[m_id].getStrength()) + summe;
	}

	m_ergebnis = Neuron::funktion(summe);
}

double Neuron::funktion(double x) {

	return tanh(/*x*x**/x*x*x*x*x*x*x*x*x);
}

double Neuron::funktionsAbleitung(double x) {

	return ((1/cos(x/10))*(1/cos(x / 10) ))/10; //4*(cosh(x)*cosh(x))/((cosh(2*x)+1)*(cosh(2*x)+1));
}

void Neuron::calcOutputGradients(double zielWert) {

	double delta = zielWert - m_ergebnis;
	m_steigung = delta * Neuron::funktionsAbleitung(m_ergebnis);
}

void Neuron::calcHiddenGradients( Layer &nextLayer) {

	double summe = steigungsSumme(nextLayer);
	m_steigung = summe * Neuron::funktionsAbleitung(m_ergebnis);
}

double Neuron::steigungsSumme( Layer &nextLayer)  {

	double summe = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {

		summe = ( m_outputStrengths[n].getStrength() * nextLayer[n].m_steigung) + summe;
	}

	return summe;
}

void Neuron::updateInputStrengths(Layer &prevLayer) {

	for (unsigned n = 0; n < prevLayer.size(); ++n) {

		Neuron &neuron = prevLayer[n];
		double oldDeltaStrength = neuron.m_outputStrengths[m_id].getDeltaStrength();
		//cout << "steigung" << m_steigung << endl;
		double newDeltaStrength = (learningRate * neuron.getOutputWert()* m_steigung) +  (alpha *oldDeltaStrength);

		//cout << "newDeltaStrength" << newDeltaStrength << endl;
		neuron.m_outputStrengths[m_id].setDeltaStrength(newDeltaStrength);
		neuron.m_outputStrengths[m_id].setStrength ( newDeltaStrength + neuron.m_outputStrengths[m_id].getStrength());

	}
}

void Neuron::printStrengths() {
	for (unsigned n = 0; n < m_outputStrengths.size(); n++) {
		cout << m_outputStrengths[n].getStrength() << endl;
	}
}


Neuron::~Neuron()
{
}

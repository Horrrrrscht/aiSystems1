#include "Neuron.h"
#include <iostream>
#include "Synapse.h"

using namespace std;


//vector<double> Neuron::m_learningVals.push_back(learningVals[0]);
//vector<double> Neuron::m_learningVals.push_back(learningVals[1]);




Neuron::Neuron(unsigned numOutputs, unsigned myId)
{
	for (unsigned c = 0; c < numOutputs; ++c) {
		m_outputStrengths.push_back(Synapse());
		m_outputStrengths.back().setStrength(randomStrength());
		m_outputStrengths.back().setDeltaStrength(m_outputStrengths.back().getStrength());
		cout << m_outputStrengths.back().getStrength() << endl;
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

	return/* tanh(x*x*x*x*x*x*x*x*x)*/ tanh(x*x*x*x*x*x*x*x*x);
}

double Neuron::funktionsAbleitung(double x) {

	return /*1/(x*x)*/ /*((1/cos(x/10))*(1/cos(x / 10) ))/10*/  9 * (x*x*x*x*x*x*x*x)*((1 / cos(x*x*x*x*x*x*x*x*x))*(1 / cos(x*x*x*x*x*x*x*x*x)))   /*3 * (x*x)*(1 / (cos(x*x*x)*cos(x*x*x)))*/;
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
		double newDeltaStrength = ((m_learningVals[0]) * neuron.getOutputWert()* m_steigung) +  ((m_learningVals[1]) *oldDeltaStrength);

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

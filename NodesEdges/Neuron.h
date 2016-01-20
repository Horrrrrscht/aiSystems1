
#ifndef NEURON_H
#define NEURON_H

#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>

#include "Synapse.h"

using namespace std;

typedef vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myId);
	void setOutputVal(double val) { m_ergebnis = val; }
	double getOutputVal(void) const { return m_ergebnis; }
	void feedForward(Layer &prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(Layer &nextLayer);
	void updateInputStrengths(Layer &prevLayer);
	vector<Synapse> &getOutputWeights() { return m_outputStrengths; }
	vector<Synapse> m_outputStrengths;
	~Neuron();

private:
	static double learningRate;
	static double alpha;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double steigungsSumme(Layer &nextLayer);
	double m_ergebnis;
	//vector<Connection> m_verbindungsStaerken;
	unsigned m_id;
	double m_steigung;
};

#endif
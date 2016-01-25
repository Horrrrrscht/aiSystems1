#pragma once
#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "Synapse.h"

#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;
class Neuron;
typedef vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myId);
	void setOutputWert(double wert) { m_ergebnis = wert; }
	double getOutputWert(void) const { return m_ergebnis; }
	void feedForward( Layer &prevLayer);
	void calcOutputGradients(double zielWert);
	void calcHiddenGradients( Layer &nextLayer);
	void updateInputStrengths(Layer &prevLayer);
	vector<Synapse> &getOutputStrengths() { return m_outputStrengths; }
	Synapse &getOutputStrength(unsigned x) { return m_outputStrengths[x]; }
	void printStrengths();
	void setLearningVals(vector<double>learningVals) { m_learningVals.clear(); m_learningVals.push_back(learningVals[0]); m_learningVals.push_back(learningVals[1]); }
	~Neuron();

private:
	static double funktion(double x);
	static double funktionsAbleitung(double x);
	double randomStrength(void) { return rand() / double(RAND_MAX); }
	double steigungsSumme( Layer &nextLayer) ;
	double m_ergebnis;
	unsigned m_id;
	double m_steigung;
	vector<double>m_learningVals;
	vector<Synapse> m_outputStrengths;
};


#endif // !NEURON_H




#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned> &layout);
	void feedForward(const vector<double> &eingabeWerte);
	void backProp(const vector<double> &zielWerte);
	void getResults(vector<double> &ergebnis);
	void printNet();

	~NeuralNet();

private:
	vector<Layer> m_layers;
	double m_fehler;
	double m_durchschnittsFehler;
	double m_durchschnittsFehlerAnpassungsWert;
};
#endif // !NEURALNET_H
#pragma once

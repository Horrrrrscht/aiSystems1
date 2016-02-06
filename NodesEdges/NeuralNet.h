#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <conio.h>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;

//das Neuronale Netz verwaltet die einzelnen Neuronen

class NeuralNet
{
public:
	NeuralNet();
	NeuralNet(const vector<unsigned> &layout, vector<double>learningVals);
	void feedForward(const vector<double> &eingabeWerte);
	void backProp(const vector<double> &zielWerte);
	void getResults(vector<double> &ergebnis);
	//void printNet();
	vector<unsigned> returnLayout() { return m_layout; }
	vector<double> returnLearningVals() { return m_learningVals; }

	~NeuralNet();

private:
	vector<Layer> m_layers;
	vector<unsigned> m_layout;
	vector<double> m_learningVals;
	double m_fehler;
	double m_durchschnittsFehler;
	double m_durchschnittsFehlerAnpassungsWert;
};
#endif // !NEURALNET_H
#pragma once

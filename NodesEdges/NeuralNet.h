#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>

using namespace std;

class Neuron;
typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned> &layout, vector<double>learningVals);
	void feedForward(const vector<double> &eingabeWerte);
	void backProp(const vector<double> &zielWerte);
	void getResults(vector<double> &ergebnis);
	void printNet();
	//unsigned getLayers(int i) {	return m_layers[i].size();}
	//void setLearningVals(vector<double>learningVals) { m_learningVals.push_back(learningVals[0]); m_learningVals.push_back(learningVals[1]); }

	~NeuralNet();

private:
	vector<Layer> m_layers;
	double m_fehler;
	double m_durchschnittsFehler;
	double m_durchschnittsFehlerAnpassungsWert;
	//vector<double> m_learningVals;
};
#endif // !NEURALNET_H
#pragma once

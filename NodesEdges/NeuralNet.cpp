#include "NeuralNet.h"
#include "Neuron.h"

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

NeuralNet::NeuralNet()
{
}

NeuralNet::NeuralNet(const vector<unsigned> &layout , vector<double>learningVals)
{

	unsigned layerAnz = layout.size();
	for (unsigned layerLoop = 0; layerLoop < layerAnz; ++layerLoop) {

		m_layers.push_back(Layer());
		unsigned numOutputs = layerLoop == layout.size() - 1 ? 0 : layout[layerLoop + 1];


		for (unsigned neuronLoop = 0; neuronLoop <= layout[layerLoop]; ++neuronLoop) {

			m_layers.back().push_back(Neuron(numOutputs, neuronLoop));

			m_layers.back().back().setLearningVals(learningVals);

			cout << "Made a Neuron!" << endl;
		}

		m_layers.back().back().setOutputWert(1.0);
	}



}

void NeuralNet::feedForward(const vector<double> &eingabeWerte) {

	assert(eingabeWerte.size() == m_layers[0].size() - 1);

	for (unsigned i = 0; i < eingabeWerte.size(); ++i) {

		m_layers[0][i].setOutputWert(eingabeWerte[i]);
	}



	for (unsigned layerLoop = 1; layerLoop < m_layers.size(); ++layerLoop) {

		Layer &prevLayer = m_layers[layerLoop - 1];

		for (unsigned n = 0; n < m_layers[layerLoop].size() - 1; ++n) {
			m_layers[layerLoop][n].feedForward(prevLayer);
		}
	}

	//printNet();
}

void NeuralNet::printNet() {


	cout << "Net Info: " << endl;

	for (unsigned layerLoop = 0; layerLoop < m_layers.size(); ++layerLoop) {

		cout << "Layer " << layerLoop << endl;

		for (unsigned n = 0; n < m_layers[layerLoop].size(); ++n) {

			cout << "Neuron " << n << endl;

			for (unsigned k = 0; k < m_layers[layerLoop][n].getOutputStrengths().size(); ++k) {

				cout << "Strength " << k << " : " << m_layers[layerLoop][n].getOutputStrength(k).getStrength() << endl;
			}
		}
	}
}

void NeuralNet::backProp(const vector<double> &zielWerte) {

	Layer &outputLayer = m_layers.back();
	m_fehler = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {

		double delta = zielWerte[n] - outputLayer[n].getOutputWert();
		m_fehler += delta * delta;
	}

	m_fehler /= outputLayer.size() - 1;
	m_fehler = sqrt(m_fehler);

	m_durchschnittsFehler = (m_durchschnittsFehler * m_durchschnittsFehlerAnpassungsWert + m_fehler) /
		(m_durchschnittsFehlerAnpassungsWert + 1.0);

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {

		outputLayer[n].calcOutputGradients(zielWerte[n]);
	}

	for (unsigned layerLoop = m_layers.size() - 2; layerLoop > 0; --layerLoop) {

		Layer &hiddenLayer = m_layers[layerLoop];
		Layer &nextLayer = m_layers[layerLoop + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {

			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	for (unsigned layerLoop = m_layers.size() - 1; layerLoop > 0; --layerLoop) {

		Layer &layer = m_layers[layerLoop];
		Layer &prevLayer = m_layers[layerLoop - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {

			layer[n].updateInputStrengths(prevLayer);
		}
	}

	//printNet();
};
void NeuralNet::getResults(vector<double> &ergebnis) {

	ergebnis.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {

		ergebnis.push_back(m_layers.back()[n].getOutputWert());
	}

};



NeuralNet::~NeuralNet()
{
}

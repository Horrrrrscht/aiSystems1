
#include "NeuralNet.h"

using namespace std;

typedef vector<Neuron> Layer;

NeuralNet::NeuralNet(const vector<unsigned> &layout)
{

	unsigned numLayers = layout.size();
	for (unsigned layerLoop = 0; layerLoop < numLayers; ++layerLoop) {
		
		m_layers.push_back(Layer());
		unsigned numOutputs = layerLoop == layout.size() - 1 ? 0 : layout[layerLoop + 1];
		

		for (unsigned neuronLoop = 0; neuronLoop <= layout[layerLoop]; ++neuronLoop) {

			m_layers.back().push_back(Neuron(numOutputs, neuronLoop));
			cout << "Made a Neuron!" << endl;
		}

		m_layers.back().back().setOutputVal(1.0);
	}



}

void NeuralNet::feedForward(const vector<double> &eingabeWerte) {

	assert(eingabeWerte.size() == m_layers[0].size() - 1);

	for (unsigned i = 0; i < eingabeWerte.size(); ++i) {

		m_layers[0][i].setOutputVal(eingabeWerte[i]);
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

			for (unsigned k = 0; k < m_layers[layerLoop][n].m_outputStrengths.size(); ++k) {

				cout << "Weight " << k << " : " << m_layers[layerLoop][n].m_outputStrengths[k].getStrength() << endl;
			}
		}
	}
}

void NeuralNet::backProp(const vector<double> &zielWerte) {

	Layer &outputLayer = m_layers.back();
	m_fehler = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1 ; ++n) {

		double delta = zielWerte[n] - outputLayer[n].getOutputVal();
		m_fehler += delta * delta;
	}

	m_fehler /= outputLayer.size() - 1;
	m_fehler = sqrt(m_fehler);

	m_durchschnittsFehler = (m_durchschnittsFehler * m_durchschnittsFehlerAnpassungsWert + m_fehler) /
		(m_durchschnittsFehlerAnpassungsWert + 1.0);

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {

		outputLayer[n].calcOutputGradients(zielWerte[n]);
	}

	for (unsigned layerLoop = m_layers.size() - 2 ; layerLoop > 0; --layerLoop) {

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

		ergebnis.push_back(m_layers.back()[n].getOutputVal());
	}

};



NeuralNet::~NeuralNet()
{
}

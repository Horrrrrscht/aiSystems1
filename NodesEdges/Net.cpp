#include "Graph.h"


using namespace std;

Net::Net(const vector<unsigned> &topology)
{

	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
		
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
		

		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {

			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			cout << "Made a Neuron!" << endl;
		}

		m_layers.back().back().setOutputVal(1.0);
	}



}

void Net::feedForward(const vector<double> &inputVals) {

	assert(inputVals.size() == m_layers[0].size() - 1);

	for (unsigned i = 0; i < inputVals.size(); ++i) {

		m_layers[0][i].setOutputVal(inputVals[i]);
	}



	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {

		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}

	cout << "Neuronen Info: " << endl;

	for (unsigned layerNum = 0; layerNum < m_layers.size(); ++layerNum) {

		cout << "Layer " << layerNum << endl;

		for (unsigned n = 0; n < m_layers[layerNum].size(); ++n) {

			cout << "Neuron " << n << endl;

			for (unsigned k = 0; k < m_layers[layerNum][n].m_outputWeights.size(); ++k) {

				cout << "Weight " << k << " : " << m_layers[layerNum][n].m_outputWeights[k].weight << endl;
			}
		}
	}
}

void Net::backProp(const vector<double> &targetVals) {

	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1 ; ++n) {

		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);

	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) /
		(m_recentAverageSmoothingFactor + 1.0);

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {

		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	for (unsigned layerNum = m_layers.size() - 2 ; layerNum > 0; --layerNum) {

		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {

			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {

		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {

			layer[n].updateInputWeights(prevLayer);
		}
	}

};
void Net::getResults(vector<double> &resultVals) {

	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {

		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}

};



Net::~Net()
{
}

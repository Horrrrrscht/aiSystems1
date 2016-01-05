#include "Graph.h"

using namespace std;

Net::Net(const vector<unsigned> &topology)
{

	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {

		m_layers.push_back(Layer());

		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {

			m_layers.back().push_back(Neuron());
			cout << "Made a Neuron!" << endl;
		}
	}

}

void Net::feedForward(const vector<double> &inputVals) {};
void Net::backProp(const vector<double> &targetVals) {};
void Net::getResults(vector<double> &resultVals) {};


Net::~Net()
{
}
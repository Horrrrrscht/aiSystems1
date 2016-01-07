// 53:02 bbbgk



#include <iostream>

#include "Node.h"
#include "Graph.h"
#include "FileReader.h"

int main()
{

	Node* node_berlin = new Node("Berlin");
	Node* node_frankfurt = new Node("Frankfurt");
	Node* node_hamburg = new Node("Hamburg");

	Graph g;
	g.addNode(node_berlin);
	g.addNode(node_frankfurt);
	g.addNode(node_hamburg);

	g.addEdge(new Edge(*node_berlin, *node_frankfurt));
	g.addEdge(new Edge(*node_frankfurt, *node_hamburg));
	g.addEdge(new Edge(*node_berlin, *node_hamburg));

	std::cout << g.toString() << std::endl;

	///////////////////////////////////////////////////////////////////
	
 	vector<vector<double>> sampleData = FileReader::readData("SampleData1.csv");
	vector<double> inputVals;
	vector<double> targetVals;

	//for (unsigned n = 0; n < sampleData.size(); ++n) {

		inputVals.push_back(sampleData[0][0]);
		inputVals.push_back(sampleData[0][1]);
		targetVals.push_back(sampleData[0][2]);





		//for (unsigned k = 0; k < sampleData[n].size(); ++k) {

		//	cout << sampleData[n][k] ;
		//}

		//cout << endl;
	//}

	///////////////////////////////////////////////////////////////////

	

	vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(1);
	Net myNet(topology);

	//

	cout << "------------------------------------------------------" << endl;
	cout << "Step 1" << endl;
	myNet.feedForward(inputVals);

	myNet.backProp(targetVals);

	cout << "------------------------------------------------------" << endl;

	vector<double> resultVals;
	myNet.getResults(resultVals);

	 




	return 0;
}




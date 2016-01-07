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
	
	vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(1);
	Net myNet(topology);

 	vector<vector<double>> sampleData = FileReader::readData("SampleData1.csv");
	
	
	
	// for (unsigned n = 0; n < sampleData.size() - 1; ++n) {
	for (unsigned n = 0; n < 5; ++n) {

		vector<double> inputVals;
		inputVals.push_back(sampleData[n][0]);
		inputVals.push_back(sampleData[n][1]);
		vector<double> targetVals;
		targetVals.push_back(sampleData[n][2]);

		cout << "------------------------------------------------------" << endl;
		cout << "Step " << n <<  endl;
		myNet.feedForward(inputVals);

		myNet.backProp(targetVals);

		vector<double> resultVals;
		myNet.getResults(resultVals);

		cout << "Input Values : " << sampleData[n][0] << " " << sampleData[n][1] << endl;
		cout << "Target Value : " << sampleData[n][2]  << endl;
		cout << "Output Value : " << resultVals[0] << endl;


		cout << "------------------------------------------------------" << endl;




		//for (unsigned k = 0; k < sampleData[n].size(); ++k) {

		//	cout << sampleData[n][k] ;
		//}

		//cout << endl;
	}

	///////////////////////////////////////////////////////////////////

	



	//






	vector<double> resultVals;
	myNet.getResults(resultVals);

	 




	return 0;
}




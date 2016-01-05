#include <iostream>

#include "Node.h"
#include "Graph.h"

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
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);
	Net myNet(topology);

	vector<double> inputVals;
	myNet.feedForward(inputVals);

	vector<double> targetVals;
	myNet.backProp(targetVals);

	//vector<double> resultVals;
	//myNet.getResults(resultVals);






	return 0;
}




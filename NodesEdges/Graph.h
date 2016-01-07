#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>


#include "Node.h"
#include "Edge.h"

using namespace std;

class Neuron ;
typedef vector<Neuron> Layer;



class Graph
{

public:

	void addNode(Node* pNode);
	
	void addEdge(Edge* pEdge);
	
	// void deleteNode(Node* pNode);

	std::string toString();

	virtual ~Graph();

	void deleteNode(Node* pNode);

private:

	std::list<Node*> m_nodes;
	std::list<Edge*> m_edges;

};

class Net : public Graph
{
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);	
	void getResults(vector<double> &resultVals) ;
	void printNet();

	~Net();

private:
	vector<Layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};



#endif
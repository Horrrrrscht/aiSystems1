#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

class Edge;
class InNode;
class HiddenNode;
class NeuralNode;
class Neuron;

typedef vector<Neuron> Layer;

struct Connection
{
	double weight;
	double deltaWeight;
};

class Node
{
public:

	Node() : m_id(generateId()) { }

	~Node();

	Node(std::string id);

	const std::string& getID() const { return m_id; }

	std::list<Edge*>& getOutgoingEdges() { return m_outgoingEdges; }

	void addOutgoingEdges(Edge* rEdge) { m_outgoingEdges.push_back(rEdge); }
	void addIncomingEdges(Edge* rEdge) { m_incomingEdges.push_back(rEdge); }

	void eraseOutgoingEdge(Edge* rEdge);
	void eraseIncomingEdge(Edge* rEdge);


private:

	std::list<Edge*> m_outgoingEdges;
	std::list<Edge*> m_incomingEdges;

	static std::string generateId();

	std::string m_id;

	static int s_numInstances;

};


class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val;  }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);
	vector<Connection> &getOutputWeights() { return m_outputWeights; }
	vector<Connection> m_outputWeights;
	~Neuron();

private:
	static double eta;
	static double alpha;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer &nextLayer) const ;
	double m_outputVal;
	//vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
};



//class InNode : public NeuralNode
//{
//public:
//	InNode();
//	~InNode();
//
//private:
//
//
//};



//class HiddenNode : public NeuralNode
//{
//public:
//	HiddenNode();
//	~HiddenNode();
//
//private:
//
//};



//class OutNode : public NeuralNode
//{
//public:
//	OutNode();
//	~OutNode();
//
//private:
//
//};

//class NeuralNode : public Node
//{
//public:
//	NeuralNode();
//	~NeuralNode();
//
//private:
//	double m_value;
//};

#endif
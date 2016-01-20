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

	 //void eraseOutgoingEdge(Edge* rEdge);
	 //void eraseIncomingEdge(Edge* rEdge);


private:

	std::list<Edge*> m_outgoingEdges;
	std::list<Edge*> m_incomingEdges;

	static std::string generateId();

	std::string m_id;

	static int s_numInstances;

};






#endif

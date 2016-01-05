#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
class Edge;
class InNode;
class HiddenNode;
class NeuralNode;


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
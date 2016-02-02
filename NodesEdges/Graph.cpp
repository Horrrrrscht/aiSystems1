#include "Graph.h"


//-------------------------------------------------------------------------------------------------

Graph::~Graph()
{

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		//Node* currentNode = *it;
		//delete currentNode;
		delete *it;
	}

	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		delete *it;
	}

}


//-------------------------------------------------------------------------------------------------

void Graph::addNode(Node* pNode)
{
	m_nodes.push_back(pNode);
}


//-------------------------------------------------------------------------------------------------

void Graph::addEdge(Edge* pEdge)
{
	m_edges.push_back(pEdge);
}


//-------------------------------------------------------------------------------------------------

std::string Graph::toString()
{
	std::string result;

	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		result += (*it)->toString() + "\n";
	}

	return result;
}


//-------------------------------------------------------------------------------------------------


//void Graph::deleteNode(Node* pNode)
//{
//
//
//	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end();)
//	{
//		if (&(*it)->getDstNode() == pNode)
//		{
//			(*it)->getSrcNode().eraseOutgoingEdge((*it));
//			delete (*it);
//			it = m_edges.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//
//	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end();)
//	{
//		if (&(*it)->getSrcNode() == pNode)
//		{
//			(*it)->getDstNode().eraseIncomingEdge((*it));
//			delete (*it);
//			it = m_edges.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//	
//	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end();)
//	{
//		if ((*it) == pNode )
//		{
//			delete (*it);
//			it = m_nodes.erase(it);
//		}
//		else
//		{
//			it++;
//		}
//	}
//}
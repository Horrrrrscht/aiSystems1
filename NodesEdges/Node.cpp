#include "Node.h"

#include <sstream>
#include <iomanip>
#include <cctype> // für isalnum() (siehe http://www.cplusplus.com/reference/cctype/isalnum/?kw=isalnum)

int Node::s_numInstances = 0;


std::string Node::generateId()
{
	std::stringstream s;
	s << "Node_" << std::setw(4) << std::setfill('0') << s_numInstances;
	return s.str();
}


Node::Node(std::string id) : m_id(id) 
{ 
	s_numInstances += 1;
}

// void Node::eraseOutgoingEdge(Edge* rEdge) 
// {
// 	for (std::list<Edge*>::iterator it = m_outgoingEdges.begin(); it != m_outgoingEdges.end();)
// 	{
// 		if ((*it) == rEdge)
// 		{
// 			it = m_outgoingEdges.erase(it);
// 		}
// 		else
// 		{
// 			it++;
// 		}
// 	}
// }

// void Node::eraseIncomingEdge(Edge* rEdge)
// {
// 	for (std::list<Edge*>::iterator it = m_incomingEdges.begin(); it != m_incomingEdges.end();)
// 	{
// 		if ((*it) == rEdge)
// 		{
// 			it = m_incomingEdges.erase(it);
// 		}
// 		else
// 		{
// 			it++;
// 		}
// 	}
// }


Node::~Node(){

}

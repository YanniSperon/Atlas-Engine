#include "Node.h"

Atlas::Node::Node(E_NodeType nodeType)
	: type(nodeType)
{
}

Atlas::Node::Node(const Node& node2)
	: type(node2.type)
{
}

Atlas::Node::~Node()
{
}

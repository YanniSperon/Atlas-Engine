#pragma once

namespace Atlas {
	class Node {
	protected:
		enum class E_NodeType {
			NONE = 0,
			THREEDIMENSIONAL, TWODIMENSIONAL
		};
		E_NodeType type;
	public:
		Node(E_NodeType nodeType);
		Node(const Node& node2);
		virtual ~Node();
	};
}
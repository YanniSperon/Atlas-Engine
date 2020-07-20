#pragma once

namespace Atlas {
	class Node {
	public:
		enum class E_NodeType {
			NONE = 0,
			THREEDIMENSIONAL, TWODIMENSIONAL
		};

		Node(E_NodeType nodeType);
		Node(const Node& node2);
		virtual ~Node();
	protected:
		E_NodeType type;
	};
}
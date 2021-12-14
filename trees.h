#pragma once

#include "nodes.h"
#include <vector>

namespace trees
{
	class Merkle
	{
	public:
		// attributes
		nodes::Node* root;
		std::vector<nodes::Node*> transactions;

		// constructors
		Merkle () : root{ nullptr } {}
		Merkle(std::vector<nodes::Node*> uTransactions);

		// methods
		std::vector<nodes::Node*> generateRootHash(std::vector<nodes::Node*>& nodes);
	};
}

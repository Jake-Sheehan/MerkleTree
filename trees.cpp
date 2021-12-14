#include "trees.h"

namespace trees
{

	/*
	* DEFAULT CONSTRUCTOR
	* 
	* This default constructor takes in a vector of transaction pointers.
	* Then, it generates the root hash, generating the entire Merkle tree
	* in the process.
	*/
	Merkle::Merkle(std::vector<nodes::Node*> uTransactions)
	{
		transactions = uTransactions;
		std::vector<nodes::Node*> rootNode = generateRootHash(transactions);
		if (rootNode.size() != 0)
		{
			// Set the root node; rootNode vector should only contain one element
			root = rootNode.at(0);
		}
		else
		{
			std::cout << "Error: no nodes; root hash not calculated" << std::endl;
		}

		
	}

	/*
	* GENERATE ROOT HASH
	* 
	* This is a recursive function that generates the root hash of the Merkle tree.
	* In the process of generating the root hash, the entire Merkle tree is generated
	*/
	std::vector<nodes::Node*> Merkle::generateRootHash(std::vector<nodes::Node*>& nodes)
	{
		// if nodes is empty, or base condition is met, return vector
		if (nodes.size() == 0 || nodes.size() == 1) return nodes;

		std::vector<nodes::Node*> parentLevel;

		// If number of nodes is odd, the final element with be hashed with itself
		if (nodes.size() % 2 != 0)
		{
			nodes.push_back(nodes.back());
		}

		// Pair adjacent nodes and create a parent node for them
		for (size_t i = 0; i < (nodes.size() - 1); i+=2)
		{
			nodes::Node* newNode = new nodes::Node(nodes.at(i), nodes.at(i + 1));
			nodes.at(i)->parent = newNode;
			nodes.at(i + 1)->parent = newNode;
			parentLevel.push_back(newNode);
		}

		// Recursive call to generate the next parent level
		return generateRootHash(parentLevel);

	}

}
#pragma once
#include <string>
#include "cryptopp/sha.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"


namespace nodes
{
	struct Node
	{
		// attributes
		std::string digest;
		Node* parent;
		Node* left; 
		Node* right;

		// constructors
		Node();
		Node(std::string uDigest);
		Node(Node* uLeft, Node* uRight);

		// methods
		void generateHash();
		void printDigest();
		bool verify(std::string uMsg);
	};

	struct Transaction : public Node
	{
		// attributes
		std::string data;

		// constructor with transaction
		Transaction(std::string uData);

		// methods
		void generateHash();
		void printTransaction();
	};
}
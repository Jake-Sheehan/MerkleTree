#include "nodes.h"

namespace nodes
{
	/*
	* NODE STRUCT
	* 
	* This structure holds a node in the Merkle tree.
	*/

	// constructors
	Node::Node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		generateHash();
	}

	Node::Node(std::string uDigest)
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		digest = uDigest;
	}

	Node::Node(Node* uLeft, Node* uRight)
	{
		parent = nullptr;
		left = uLeft;
		right = uRight;
		generateHash();
	}

	// Generates a hash from children and sets left and right children
	void Node::generateHash()
	{
		if (left == nullptr && right == nullptr)
		{
			digest = "";
			return;
		}
		else if (left == nullptr && right != nullptr)
		{
			digest = right->digest;
		}
		else if (left != nullptr && right == nullptr)
		{
			digest = left->digest;
		}
		else
		{
			std::string data;
			// add hashes of children
			data += left->digest;
			data += right->digest;
			// hash object init
			CryptoPP::SHA256 hash;
			// update hash object with transaction data
			hash.Update((const CryptoPP::byte*)data.data(), data.size());
			// resize digest to standard digest size
			digest.resize(hash.DigestSize());
			// calculate the hash
			hash.Final((CryptoPP::byte*)&digest[0]);
		}

	}

	// verfies a message matches a hash
	bool Node::verify(std::string uMsg)
	{
		// Init hash object
		CryptoPP::SHA256 hash;
		// update hash object with uMsg data
		hash.Update((const CryptoPP::byte*)uMsg.data(), uMsg.size());
		// verify uMsg against transaction data
		return hash.Verify((const CryptoPP::byte*)digest.data());
	}

	// prints the digest as hex
	void Node::printDigest()
	{
		// sets up hex encoder to encode bytes to hex using std::cout
		CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
		// prints digest using StringSource pipeline
		std::cout << "Digest: ";
		CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder)); // prints digest
		std::cout << std::endl;
	}

	/*
	* TRANSACTION STRUCT
	* 
	* This structure holds the initial transaction data.
	* It in a sub-structure of Node.
	*/

	// constructor with transaction
	Transaction::Transaction(std::string uData)
	{
		data = uData;
		generateHash();
	}

	// hashes the transaction data
	void Transaction::generateHash()
	{
		// hash object init
		CryptoPP::SHA256 hash;
		// update hash object with transaction data
		hash.Update((const CryptoPP::byte*)data.data(), data.size());
		// resize digest to standard digest size
		digest.resize(hash.DigestSize());
		// calculate the hash
		hash.Final((CryptoPP::byte*)&digest[0]);
	}

	// prints transaction
	void Transaction::printTransaction()
	{
		std::cout << "Transaction: " << data << std::endl;
	}

}
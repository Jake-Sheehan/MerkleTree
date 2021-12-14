/*
* Merkle Tree
* 
* author       :  Jake Sheehan
* institution  :  Southern New Hampshire University
* class        :  CS-499 Computer Science Capstone
* profesor     :  Prof. Brooke
* 
* This Merkle tree can be used to verify the integrity of transactions
* sent as a block. The challenger can feed the transactions into this program
* and compare the root hash to the sender's root hash. If they match, the integrity
* of the transactions list is verified.
* 
* NOTES: 
* - The compiler might show warnings, but they are related to CryptoPP itself,
* not my code. 
* 
* - The use of CryptoPP here is derived from the CryptoPP wiki here https://www.cryptopp.com/wiki/SHA2
* 
* - CryptoPP is a widely accepted standard for encryption in C++.
* 
*/

#include <iostream>
#include "nodes.h"
#include "trees.h"


int main() {

	/*
	* TRANSACTION STRINGS AND VECTOR
	* 
	* The transactions here can contain any information (feel free to change it), 
	* but adding or deleting transactions in this program will break 
	* the manual verification test.
	*/
	std::vector<std::string> transactionSet{ 
		"Sender: Bob; Receiver: Alice; Amount: 465",  
		"Sender: Bella; Receiver: Lily, Amount: 24",  
		"Sender: Jake; Receiver: Allie, Amount: 987", 
		"Sender: Bella; Receiver: Jake, Amount: 5"
	};

	// Create transaction objects
	std::vector<nodes::Node*> transactions;

	// Add transaction objects to a vector
	for (const auto& transaction : transactionSet)
	{
		transactions.push_back(new nodes::Transaction(transaction));
	}

	/*
	* MERKLE TREE
	* 
	* The Merkle tree is created from the vector of transactions and
	* the digest is printed. The digest that is printed is not raw data,
	* but encoded using the CryptoPP hex encoder to make is readable.
	*/

	// Pass transactions vector to create Merkle Tree
	trees::Merkle mt = trees::Merkle(transactions);
	std::cout << "--- Merkle Tree Root Digest ---" << std::endl;
	mt.root->printDigest();
	std::cout << std::endl;

	/*
	* TEST: MANUALLY VERIFY MERKLE TREE
	* 
	* All the following code is a test to verify the Merkle tree is functioning properly.
	* Here, we manually calulate the hashes of the transactions, then caluclate
	* the hashes for the parent level, and finally the root hash. The root hash is then
	* printed using the CryptoPP hex encoder so it can be compared to the root hash calculated
	* by the Merkle tree implementation. As an added test, CryptoPP is used to verify that the 
	* Merkle tree root hash and the manually calculated root hash are indeed the same.
	* This test is intended to prove that the Merkle tree implementation functions properly.
	*/

	/*
	* Initial transaction hashes
	*/

	// hash transaction 1
	std::string h1{};
	// hash object init
	CryptoPP::SHA256 hash1;
	// update hash object with transaction data
	hash1.Update((const CryptoPP::byte*)transactionSet.at(0).data(), transactionSet.at(0).size());
	// resize digest to standard digest size
	h1.resize(hash1.DigestSize());
	// calculate the hash
	hash1.Final((CryptoPP::byte*)&h1[0]);

	// hash transaction 2
	std::string h2{};
	// hash object init
	CryptoPP::SHA256 hash2;
	// update hash object with transaction data
	hash2.Update((const CryptoPP::byte*)transactionSet.at(1).data(), transactionSet.at(1).size());
	// resize digest to standard digest size
	h2.resize(hash2.DigestSize());
	// calculate the hash
	hash2.Final((CryptoPP::byte*)&h2[0]);

	// hash transaction 3
	std::string h3{};
	// hash object init
	CryptoPP::SHA256 hash3;
	// update hash object with transaction data
	hash3.Update((const CryptoPP::byte*)transactionSet.at(2).data(), transactionSet.at(2).size());
	// resize digest to standard digest size
	h3.resize(hash3.DigestSize());
	// calculate the hash
	hash3.Final((CryptoPP::byte*)&h3[0]);

	// hash transaction 4
	std::string h4{};
	// hash object init
	CryptoPP::SHA256 hash4;
	// update hash object with transaction data
	hash4.Update((const CryptoPP::byte*)transactionSet.at(3).data(), transactionSet.at(3).size());
	// resize digest to standard digest size
	h4.resize(hash4.DigestSize());
	// calculate the hash
	hash4.Final((CryptoPP::byte*)&h4[0]);

	/*
	* Parent level hashes
	*/

	std::string p1 = h1 + h2;
	std::string hp1{};
	// hash object init
	CryptoPP::SHA256 hash5;
	// update hash object with transaction data
	hash5.Update((const CryptoPP::byte*)p1.data(), p1.size());
	// resize digest to standard digest size
	hp1.resize(hash5.DigestSize());
	// calculate the hash
	hash5.Final((CryptoPP::byte*)&hp1[0]);

	std::string p2 = h3 + h4;
	std::string hp2{};
	// hash object init
	CryptoPP::SHA256 hash6;
	// update hash object with transaction data
	hash6.Update((const CryptoPP::byte*)p2.data(), p2.size());
	// resize digest to standard digest size
	hp2.resize(hash6.DigestSize());
	// calculate the hash
	hash6.Final((CryptoPP::byte*)&hp2[0]);

	/*
	* Root level hashes
	*/

	std::string root = hp1 + hp2;
	std::string rootDigest{};
	// hash object init
	CryptoPP::SHA256 hash7;
	// update hash object with transaction data
	hash7.Update((const CryptoPP::byte*)root.data(), root.size());
	// resize digest to standard digest size
	rootDigest.resize(hash7.DigestSize());
	// calculate the hash
	hash7.Final((CryptoPP::byte*)&rootDigest[0]);

	/*
	* PRINT ROOT DIGEST
	*/

	std::cout << "--- Manual Calculation Root Digest ---" << std::endl;
	// sets up hex encoder to encode bytes to hex using std::cout
	CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
	// prints digest using StringSource pipeline
	std::cout << "Digest: ";
	CryptoPP::StringSource(rootDigest, true, new CryptoPP::Redirector(encoder)); // prints digest
	std::cout << std::endl;
	std::cout << std::endl;

	/*
	* VERIFY USING CRYPTOPP
	*/
	std::cout << "--- CryptoPP Verification ---" << std::endl;
	if (mt.root->verify(root))
	{
		std::cout << "Verified" << std::endl;
	}
	else
	{
		std::cout << "Not Verified" << std::endl;
	}

	return 0;
}
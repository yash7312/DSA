#include "trie.h"
#include <iostream>
#include <sstream> // Add this line to include the <sstream> header

Trie::Trie()
{
	root = new TrieNode();
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	// TrieNode* curr = new TrieNode();
	// for(int i = 0; i < 26; i++){
	// 	curr->children[i] = NULL;
	// }
	// return curr;
	return root;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	TrieNode* curr = this->root;
	
	for(int i=0; i<key.length(); i++){
		int index = int(key[i] - 'a');
		if(curr->children[index] == NULL){
			curr->children[index] = new TrieNode();
		}
		
		curr = curr->children[index];
		// if(curr->isWordEnd != 1) curr->isWordEnd = 0;
	}
	curr->isWordEnd = true;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	TrieNode* curr = root;
	bool success = 1;
	for(int i=0; i<key.length(); i++){
		int index = int(key[i] - 'a');
		if(curr->children[index] == NULL && key[i] != '\0'){
			success = 0;
			break;
		}
		curr = curr->children[index];
	}

	if(success && curr->isWordEnd == 1){
		return success;
	}
	else {
		return success;
	}
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	
	for(int i = 0; i < 26; i++){
		if(root->children[i] != NULL) return 0;
	}
	
	return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	if(root->isWordEnd == 1){
		std::cout << currPrefix << std::endl;
	}
	
	TrieNode* curr = root;

	for(int i=0; i<26; i++){
		if(curr->children[i] != NULL){
			suggestionsRec(curr->children[i], currPrefix + std::string(1, char(i + 'a')));
		}
	}
	
}

// print suggestions for given query prefix.
// #include <queue>
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	TrieNode* curr = this->root;
	for(char i: query){
		if(curr->children[i - 'a'] == NULL) return 0;
		if(i == '#') break;
		curr = curr->children[i - 'a'];
	}

	this->suggestionsRec(curr, query);

	return 1;
}
// Process the file "lorem.txt" to insert the words in lorem.txt and store the relevant context as needed.

#include <fstream>

void Trie::processContext()
{
	std::ifstream file("lorem.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string word;
			while (iss >> word) {
				insert(root, word);
			}
		}
		file.close();
	}
}


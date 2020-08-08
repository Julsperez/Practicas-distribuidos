#include <bits/stdc++.h>
#include <string>


using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	bool isWord;
};

struct TrieNode *getNode();
void insert(struct TrieNode *, string);
bool search(struct TrieNode *, string);

int main() {
	string keys[] = {"the", "a", "there", "answer"};
	int n = sizeof(keys)/sizeof(keys[0]);
	cout << "sizeof(keys): " << sizeof(keys) << endl;
	cout << "sizeof(keys[0]): " << sizeof(keys[0]) << endl;
	cout << "n: " << n << endl;
	
	struct TrieNode *root = getNode();

	for(int i = 0; i < n; i++) 
		insert(root, keys[i]);

	search(root, "the")? cout << "yes\n" : cout << "no\n";
	search(root, "these")? cout << "yes\n" : cout << "no\n";
	search(root, "answer")? cout << "yes\n" : cout << "no\n";
	search(root, "an")? cout << "yes\n" : cout << "no\n";

	return 0;
}

// ----------------------------------

struct TrieNode *getNode() {
	struct TrieNode *pNode = new TrieNode;
	pNode -> isWord = false;

	for(int i = 0; i < ALPHABET_SIZE; i++) {
		pNode -> children[i] = NULL;
	}

	return pNode;
}

void insert(struct TrieNode *root, string key){
	struct TrieNode *pCrawl = root;

	for(int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		cout << "insert:index " << index << endl;
		if(!pCrawl -> children[index])
			pCrawl -> children[index] = getNode();
		pCrawl = pCrawl -> children[index];
	}
	pCrawl -> isWord = true;
}

bool search(struct TrieNode *root, string key) {
	struct TrieNode *pCrawl = root;
	for(int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		cout << "search:index " << index << endl;
		if(!pCrawl -> children[index])
			return false;
		pCrawl = pCrawl -> children[index];
	}
	return (pCrawl != NULL && pCrawl -> isWord);
}


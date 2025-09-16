#pragma once
#include <iostream>

#define ALPHABET_SIZE 26

struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	bool isEndWord;
	int freq = 0;
};

TrieNode* getNewNode();
void insert(TrieNode* root, std::string key);
bool search(TrieNode* root, std::string key);
bool isEmpty(TrieNode* root);


TrieNode* remove(TrieNode* root, std::string key, int depth = 0);

void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res);

void autocomplete(TrieNode* root, std::string& key);
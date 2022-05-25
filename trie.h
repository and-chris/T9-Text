#pragma once

#define MAX_WORD_LENGTH 40
#define NUM_CHILDREN 11
#define POUND 10


struct TrieNode {
  char* word;
  struct TrieNode* children[NUM_CHILDREN];
};

/*
 * allocates a TrieNode and returns a pointer to it.
 * Must eventually be freed by trieNode_free
 */
struct TrieNode* trieNode_new();

/*
 * Return a pointer to the word inside of the node.
 * NOT a pointer to a copy of the word. If there is no
 * word then return NULL. 
 *
 * This function is required for external testing purposes 
 * and would not be useful for implementing search/insert
 * if you need a non-const pointer to the word
 */
const char* trieNode_getWord(const struct TrieNode* node);

/*
 * Return a pointer to child i of the node.
 * Convention is that i will never be 0 or 1.
 * i = 2-9 are T9 letters, and i=10 is #
 * NOT a pointer to a copy of the child.
 *
 * This function is required for external testing purposes 
 * and would not be useful for implementing search/insert
 * if you need a non-const pointer to the child
 */
const struct TrieNode* trieNode_getChild(const struct TrieNode* node, int i);

/*
 * For the trie rooted at root, return pointer to TrieNode
 * whose word corresponds to
 * the given integer code.
 * codelength is the number of integers in the code. See trieNode_getChild
 * for meaning of each code from 2 to 10. 
 */
struct TrieNode* trieNode_search(struct TrieNode* root, const int* code, int codelength);

/*
 * insert the given word into the trie rooted at root.
 */
void trieNode_insert(struct TrieNode* root, const char* word); 

/*
 * free the heap memory associated with the trie rooted at root
 */
void trieNode_free(struct TrieNode* root);

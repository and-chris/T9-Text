/*
1.Andrew Christopher
2.Spring 2022
3.This appllication creates implements T9 predictive text like that used in old flip phone key pads
*/
#include <stdio.h>
#include "trie.h"
#include <string.h>
#include <stdlib.h>

//This function creates a new node in the Trie
struct TrieNode* trieNode_new(){
  struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
  node->word=NULL;
  for(int i =0; i<NUM_CHILDREN; i++){
    node->children[i]=NULL;
  }
  return node;
}

//This function returns the word of the inputted node. Returns in null if there is no word
const char* trieNode_getWord(const struct TrieNode* node){
  if(node->word == NULL){
    return NULL;
  }
  return node->word; 
}

//This function returns the ith child of the given node
const struct TrieNode* trieNode_getChild(const struct TrieNode* node, int i){
  return node->children[i];
}

//This function converts a given letter into an integer based on table. 2='a,b,c', etc.
int word_to_key(char letter){
  int table[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
  int x = letter-'a';
  int key = table[x];
  return key; 
}

//This function searches for the given code from the root node. returns the node corresponding to the code
struct TrieNode* trieNode_search(struct TrieNode* root, const int* code, int codelength){
  struct TrieNode* curr = root;
  for(int i=0;i<codelength;i++){
    if(code[i]!= '#'){
      if(curr->children[code[i]]==NULL){
        return NULL;
      }
      curr=curr->children[code[i]];
    }else if(curr->children[10]==NULL){
      return NULL;
      
    }else{
      curr=curr->children[10];
    }
    }
  return curr;
}


//This function inserts a node based on the given word
void trieNode_insert(struct TrieNode* root, const char* word){
  
  int wordlength = strlen(word);
  char *text = (char *)malloc(MAX_WORD_LENGTH* sizeof(char));
  if(text!=NULL){
    strncpy(text,word,wordlength);
    text[wordlength]='\0';
  }
  int i=0;
  
  while(word[i] != '\0'){
    int index=word_to_key(word[i]);
    if(root->children[index]==NULL){
      root->children[index]=trieNode_new();
      
    }
    root=root->children[index];
    i++;
  }
  while(root->children[10]!=NULL){
    root=root->children[10];
  }
  
  if(root->word == NULL){
    root->word=text;
  }else{
    root->children[10]=trieNode_new();
    root=root->children[10];
    root->word=text;
  }
  }


//This function frees up the malloc'd memory.
void trieNode_free(struct TrieNode* root){
  for(int i=0; i<11;i++){
    if(root->children[i] != NULL){
      trieNode_free(root->children[i]);
  } 
}
  if(root->word != NULL){
    free(root->word);
  }
  free(root);
}

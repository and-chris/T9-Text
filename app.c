/*
1.Andrew Christopher
2.Spring 2022
3.This appllication creates implements T9 predictive text like that used in old flip phone key pads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"

#define BUFFER_LEN 100


int main(int argc, char **argv){
  struct TrieNode* root= trieNode_new();
  if(argc<2){
    printf("missing FILE argument\n");
    exit(1);
  }
  char* filename=argv[1];
  FILE * file;
  char buffer[BUFFER_LEN];
  file=fopen(filename, "r");
  while(fgets(buffer,BUFFER_LEN, file)){
    trieNode_insert(root,buffer);
  }
  fclose(file);
  
  printf("Enter \"exit\" to quit.\n");
  char number[100];
  int control=1;
  struct TrieNode* curr =root;
  
  while(control){
    printf("Enter Key Sequence. \"#\" for next word.\n");
    scanf("%s",number);
    if(strcmp("exit", number) != 0){
      int digit[MAX_WORD_LENGTH];
      for(int i=0; i<strlen(number);i++){
        digit[i]=number[i]-'0';
      }
      if(number[0] != '#'){
        curr = trieNode_search(root, digit, strlen(number));
      }else{ 
        curr=trieNode_search(curr, digit,strlen(number));
      }
      if(curr != NULL){
        
        if(trieNode_getWord(curr)){
          printf("\'%s\'\n",trieNode_getWord(curr));
        }else{
          printf("Not found in current dictionary.\n");
        }
      }else{
        if(number[strlen(number)-1]=='#'){
          printf("There are no more T9onyms\n");
        }else{
          printf("Not found in current dictionary.\n");
        }
      }
    }else{
      control=0;    
    }
  }
  
  trieNode_free(root);
  return 0;  
}




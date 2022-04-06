
#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"linkedList.h"
#define CONSTANT 100


//BST

typedef struct elm{
	char word[50];
	int appearCount;
	dblist *rootLine, *curLine, *tailLine;
}elmType;

typedef struct node_type{
  elmType element;
  struct node_type *left,*right;
}nodeType;

typedef nodeType *treetype;//treetype a <=> nodeType* a

void makeNullTree(treetype* N){
  (*N)=NULL;
}

nodeType* Create_Node(elmType data){
  nodeType* New = (nodeType*)malloc(sizeof(nodeType));
  if(New!=NULL){
	  New->element=data;
	  New->left=NULL;
	  New->right=NULL;
  }
  return New;
}

int isEmptyTree(treetype N){
	return N==NULL;
}

treetype leftChild(treetype N){
	if(N!=NULL)return N->left;
	else return NULL;
}

treetype rightChild(treetype N){
	if(N!=NULL)return N->right;
	else return NULL;
}

int Compare(elmType a, elmType b){
	if(strcmp(a.word,b.word	)>0)return 1;
	else if(strcmp(a.word,b.word)<0) return -1;
	else return 0;
}

void insertNode(treetype* T,elmType data){
	if(*T==NULL)(*T)=Create_Node(data);
	else{
		if(Compare(data,(*T)->element)==1)insertNode(&(*T)->right,data);
		else insertNode(&(*T)->left,data);
	}
}

int isLeaf(treetype N){
	if(isEmptyTree(N)){
		return 0;
	}
	else return(N->left==NULL&&N->right==NULL);
}

int countNode(treetype N){
	if(isEmptyTree(N))return 0;
	else return 1+countNode(N->left)+countNode(N->right);
}

void InOrderPrint(treetype T){
	if(T!=NULL){
		InOrderPrint(T->left);
		printf("%s %d", T->element.word, T->element.appearCount);
		traversinglist(T->element.rootLine);
		printf("\n");
		InOrderPrint(T->right);
		
	}
}

int Max(int a, int b){
	if(a>b)return a;
	else return b;
}

int treeHeight(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+ Max(treeHeight(T->left),treeHeight(T->right));
	}
}

int leafNode(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 1;
		else return leafNode(T->left)+leafNode(T->right);
	}
}

int innerNode(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+innerNode(T->left)+innerNode(T->right);
	}
}

int numRight(treetype T){
	if(T==NULL){
		return 0;
	}
	else{
		if(T->right==NULL)return 0+numRight(T->left);
		else return 1+numRight(T->left)+numRight(T->right);
	}
}

treetype searchT(treetype T, elmType x){//Search
	if(T==NULL) return T;
	if(Compare(x,T->element)==0) return T;
	else if(isLeaf(T))return NULL;
	else if(Compare(x,T->element)==1)return searchT(T->right,x);
	else return searchT(T->left,x);
}

elmType deletemin(treetype *n){
  elmType k;
  if((*n)->left == NULL){
    k = (*n)->element;
    (*n) = (*n)->right;
    return k;
  }
  else 
    return deletemin(&(*n)->left);
}
void deleteNode(treetype *n, elmType key){
  if(*n!=NULL){
    if(Compare(key,(*n)->element)==-1)
      deleteNode(&(*n)->left,key);
    else if(Compare(key,(*n)->element)==1)
      deleteNode(&(*n)->right,key);
    else if((*n)->left == NULL && (*n)->right == NULL)
      *n = NULL;
    else if((*n)->left == NULL)
      *n = (*n)->right;
    else if((*n)->right == NULL)
      *n = (*n)->left;
    else
      (*n)->element = deletemin(&(*n)->right);
  }
}
void freeTree(treetype T){
	if(T==NULL) return;
	freeTree(T->left);
	freeTree(T->right);
	freeNode(&(T->element.rootLine));
	free((void*)T);
}
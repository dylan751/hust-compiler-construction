#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"linkedList.h"

//BST
typedef struct elm{
	char word[50];
	int appearCount;
	dblist *rootLine, *curLine, *tailLine;
}elementType;

typedef struct node_type{
  elementType element;
  struct node_type *left,*right;
}nodeType;

typedef nodeType *treeType;//treeType a <=> nodeType* a

void makeNullTree(treeType* N){
  (*N)=NULL;
}

nodeType* Create_Node(elementType data){
  nodeType* New = (nodeType*)malloc(sizeof(nodeType));
  if(New!=NULL){
	  New->element=data;
	  New->left=NULL;
	  New->right=NULL;
  }
  return New;
}

int isEmptyTree(treeType N){
	return N==NULL;
}

treeType leftChild(treeType N){
	if(N!=NULL)return N->left;
	else return NULL;
}

treeType rightChild(treeType N){
	if(N!=NULL)return N->right;
	else return NULL;
}

int Compare(elementType a, elementType b){
	if(strcmp(a.word,b.word	)>0)return 1;
	else if(strcmp(a.word,b.word)<0) return -1;
	else return 0;
}

void insertNode(treeType* T,elementType data){
	if(*T==NULL)(*T)=Create_Node(data);
	else{
		if(Compare(data,(*T)->element)==1)insertNode(&(*T)->right,data);
		else insertNode(&(*T)->left,data);
	}
}

int isLeaf(treeType N){
	if(isEmptyTree(N)){
		return 0;
	}
	else return(N->left==NULL&&N->right==NULL);
}

int countNode(treeType N){
	if(isEmptyTree(N))return 0;
	else return 1+countNode(N->left)+countNode(N->right);
}

void InOrderPrint(treeType T){
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

int treeHeight(treeType T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+ Max(treeHeight(T->left),treeHeight(T->right));
	}
}

int leafNode(treeType T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 1;
		else return leafNode(T->left)+leafNode(T->right);
	}
}

int innerNode(treeType T){
	if(T==NULL){
		return 0;
	}
	else{
		if(isLeaf(T))return 0;
		else return 1+innerNode(T->left)+innerNode(T->right);
	}
}

int numRight(treeType T){
	if(T==NULL){
		return 0;
	}
	else{
		if(T->right==NULL)return 0+numRight(T->left);
		else return 1+numRight(T->left)+numRight(T->right);
	}
}

treeType searchTree(treeType T, elementType x){//Search
	if(T==NULL) return T;
	if(Compare(x,T->element)==0) return T;
	else if(isLeaf(T))return NULL;
	else if(Compare(x,T->element)==1)return searchTree(T->right,x);
	else return searchTree(T->left,x);
}

elementType deletemin(treeType *n){
  elementType k;
  if((*n)->left == NULL){
    k = (*n)->element;
    (*n) = (*n)->right;
    return k;
  }
  else 
    return deletemin(&(*n)->left);
}
void deleteNode(treeType *n, elementType key){
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
void freeTree(treeType T){
	if(T==NULL) return;
	freeTree(T->left);
	freeTree(T->right);
	freeNode(&(T->element.rootLine));
	free((void*)T);
}
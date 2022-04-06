#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

//Linklist
typedef int elementtype; //Must fix

struct list_el{
  elementtype element;
  struct list_el *next;
  struct list_el *prev;
};
typedef struct list_el dblist;

void makeNullList(dblist **root,dblist **cur,dblist **tail){
  *root=NULL;
  *cur=NULL;
  *tail=NULL;
}

dblist* makeNewNode(elementtype data){
  dblist *New = (dblist*)malloc(sizeof(dblist));
  New->element=data;
  New->next = NULL;
  New->prev = NULL;
  return New;
}

void displayNode(dblist* p){ //Must fix
  if(p==NULL){
    printf("ERROR pointer NULL\n");
    return;
  }
  printf(", %d",p->element);
}

void traversinglist(dblist *root){
	dblist *cur;
  for(cur=root;cur!=NULL;cur=cur->next){
    displayNode(cur);
  }
}

void insertAtHead(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
  if(*root==NULL){
   	*root=New;
 		*tail=New;
 		*cur=*root;
  }
  else{
  	New->next=*root;
  	(*root)->prev=New;
  	*root=*cur=New;
	}
}

void AppendList(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
  if((*root)==NULL){
   	(*root)=New;
 		(*tail)=New;
 		(*cur)=(*root);
 		New->next = New->prev = NULL;
  }
  else{
  	New->prev=(*tail);
  	(*tail)->next=New;
  	(*tail)=(*cur)=New;
  	New->next = NULL;
	}
}

void insertAfterCur(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
	if(*root==NULL){
		*root=New;
 		*tail=New;
 		*cur=*root;
	}
	else if(*cur==NULL){
		printf("ERROR! There is no current.");
		return;
	}
	else{
		if(*cur==*tail){
			(*cur)->next=New;
			New->prev=*cur;
			*tail=*cur=New;
		}
		else{
			New->next=(*cur)->next;
			New->prev=*cur;
			(*cur)->next->prev=New;
			(*cur)->next=New;
			*cur=New;
		}
	}
}

void insertBeforeCur(elementtype data,dblist **root,dblist **cur,dblist **tail){
	dblist* New=makeNewNode(data);
	if(*root==NULL){
		*root=New;
 		*tail=New;
 		*cur=*root;
	}
	else if(*cur==NULL){
		printf("ERROR! There is no current.");
		return;
	}
	else{
		if(*cur==*root){
			(*cur)->prev=New;
			New->next=*cur;
			*root=*cur=New;
		}
		else{
			New->next=*cur;
			New->prev=(*cur)->prev;
			(*cur)->prev->next=New;
			(*cur)->prev=New;
			*cur=New;
		}
	}
}


void insertAtPos(elementtype data,dblist **root,dblist **cur,dblist **tail,int p){//Dem tu 0
	int i;
	if(p==0){
		insertAtHead(data,root,cur,tail);
		return;
	}
	if(*root==NULL){
		printf("There is no list");
		return;
	}
	for(i=0,*cur=*root;i<p;i++){
		if(*cur==*tail){
			if(i==p-1){
				AppendList(data,root,cur,tail);
				return;
			}
			else{
				printf("Not enough element\n");
				return;
			}
		}
		*cur=(*cur)->next;
	}
	insertBeforeCur(data,root,cur,tail);
}

void deleteFirstElement(dblist **root,dblist **cur,dblist **tail){
	if(*root!=NULL){
		if(*root==*tail){
			free(*root);
			makeNullList(root,cur,tail);
		}
		else{
			dblist *to_free;
			to_free=*root;
			*root=(*root)->next;
			(*root)->prev=NULL;
			free(to_free);
			*cur=*root;
		}
	}
}

void deleteLastElement(dblist **root,dblist **cur,dblist **tail){
	if(*tail!=NULL){
		if(*root==*tail){
			free(*root);
			makeNullList(root,cur,tail);
		}
		else{
			dblist *to_free;
			to_free=*tail;
			*tail=(*tail)->prev;
			(*tail)->next=NULL;
			free(to_free);
			*cur=*tail;
		}
	}
}

void deleteCurElement(dblist **root,dblist **cur,dblist **tail){
	if(*cur!=NULL){
		if(*cur==*root){
			deleteFirstElement(root,cur,tail);
		}
		else if(*cur==*tail){
			deleteLastElement(root,cur,tail);
		}
		else{
			dblist* to_free;
			(*cur)->next->prev=(*cur)->prev;
			(*cur)->prev->next=(*cur)->next;
			to_free=*cur;
			*cur=(*cur)->next;
			free(to_free);
		}
	}
}

void deleteAtPos(dblist **root,dblist **cur,dblist **tail,int p){//Bat dau dem tu 0
	if(*root!=NULL){
		int i;
		for(i=0,*cur=*root;i<p;i++){
			if((*cur)->next==NULL){
				printf("Not enough element\n");
				return;
			}
			*cur=(*cur)->next;
		}
		deleteCurElement(root,cur,tail);
	}
}

void list_reverse(dblist **root,dblist **cur,dblist **tail){
	dblist *tmp;
	*cur=*root;
	while(*cur!=NULL){
		tmp=(*cur)->next;
		(*cur)->next=(*cur)->prev;
		(*cur)->prev=tmp;
		*cur=tmp;
	}
	tmp=*root;
	*cur=*root=*tail;
	*tail=tmp;
}

void freeNode(dblist **root){
	dblist *to_free;
	for(to_free=*root;to_free!=NULL;to_free=*root){
    *root=to_free->next;
    free(to_free);
  }
}

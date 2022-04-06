#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>
#define CONSTANT 100

#include"tree.h"

treetype searchTbyword(treetype T, char* word){//Search
	elmType wordData;
	strcpy(wordData.word, word);
	return searchT(T, wordData);
}

void AddWord(treetype* wordTree ,char *word, int line){
	treetype curword = searchTbyword(*wordTree, word);
	if(curword==NULL){//new
		elmType wordData;
		strcpy(wordData.word, word);
		wordData.appearCount=1;
		makeNullList(&(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		AppendList(line, &(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		insertNode(wordTree, wordData);
	}
	else{
		curword->element.appearCount++;
		AppendList(line, &(curword->element.rootLine), &(curword->element.curLine), &(curword->element.tailLine));
	}
}

void ReadFile(char* fileName ,treetype* wordTree, treetype* stopTree){
	char c, prevC;
	int count, line;
	char word[20];
	bool danhTuRieng, isAword;
	FILE *ptr=fopen(fileName,"r");
	if(ptr==NULL){
		printf("cant open %s\n", fileName);
		return;
	}
	for(count=0, line=1, prevC='f', isAword = false, danhTuRieng = false;(c=fgetc(ptr))!=EOF; prevC = c){
		// printf("%c",c);
		if(c>=65&&c<=90){//Upper
			c+=32;
			if(prevC==' '){//danh tu rieng
				danhTuRieng=true;
			}
		}

		if(c<97 || c>122){//end word
			if(!danhTuRieng && isAword){//save
				word[count]='\0';
				if(searchTbyword(*stopTree, word)==NULL){
					
					// printf("%s %d\n", word, line);
					AddWord(wordTree, word, line);
				}
			}

			count=0;
			danhTuRieng=false;
			isAword=false;

			if(c=='\n'){
				line++;
			}
		}
		else{
			if(!isAword) isAword=true;
			word[count++]=c;
		}
	}
	fclose(ptr);
}

int main(int argc, char const *argv[])
{
	treetype wordTree, stopTree;
	makeNullTree(&wordTree);
	makeNullTree(&stopTree);
	
	ReadFile("../stopw.txt", &stopTree, &wordTree);//build stop word

	ReadFile("../alice30.txt", &wordTree, &stopTree);//buil need to read word

	InOrderPrint(wordTree);
	// InOrderPrint(stopTree);

	freeTree(wordTree);
	freeTree(stopTree);
	return 0;
}
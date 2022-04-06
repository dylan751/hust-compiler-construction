#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include<stdlib.h>

#include"tree.h"

treeType searchTreeByWord (treeType T, char* word) {//Search
	elementType wordData;
	strcpy(wordData.word, word);
	return searchTree(T, wordData);
}

void AddWord (treeType* wordTree ,char *word, int line) {
	treeType currentWord = searchTreeByWord(*wordTree, word);
	if (currentWord == NULL) {
		elementType wordData;
		strcpy(wordData.word, word);
		wordData.appearCount=1;
		makeNullList(&(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		AppendList(line, &(wordData.rootLine), &(wordData.curLine), &(wordData.tailLine));
		insertNode(wordTree, wordData);
	}
	else {
		currentWord->element.appearCount++;
		AppendList(line, &(currentWord->element.rootLine), &(currentWord->element.curLine), &(currentWord->element.tailLine));
	}
}

void ReadFile (char* fileName ,treeType* wordTree, treeType* stopTree) {
	char c, prevC;
	int count, line;
	char word[20];
	bool properNouns, isWord;
	FILE *fptr=fopen(fileName,"r");
	if (fptr == NULL) {
		printf("Cannot open %s\n", fileName);
		return;
	}
	for (count = 0, line = 1, prevC = 'a', isWord = false, properNouns = false;(c=fgetc(fptr)) != EOF; prevC = c) {
		// If the first letter is Uppercase and not at the first of the line -> properNouns
		if (c >= 'A' && c <= 'Z') {
			c += 32; // ASCII
			if (prevC == ' ') {
				properNouns = true;
			}
		}

		if (c < 'a' || c > 'z') {
			// Save
			if (!properNouns && isWord) {
				word[count] = '\0';
				if (searchTreeByWord(*stopTree, word)==NULL) {
					AddWord(wordTree, word, line);
				}
			}

			count = 0;
			properNouns = false;
			isWord = false;

			if (c == '\n') {
				line++;
			}
		}
		else {
			if (!isWord) isWord=true;
			word[count++]=c;
		}
	}
	fclose(fptr);
}

int main (int argc, char const *argv[]) {
	treeType wordTree, stopTree;
	makeNullTree(&wordTree);
	makeNullTree(&stopTree);
	
	ReadFile("../textFiles/stopw.txt", &stopTree, &wordTree);//build stop word

	ReadFile("../textFiles/alice30.txt", &wordTree, &stopTree);//buil need to read word

	InOrderPrint(wordTree);

	freeTree(wordTree);
	freeTree(stopTree);
	return 0;
}
#pragma once
typedef struct WORDDICT {
	char c;
	int isword;
	struct WORDDICT* bro;
	struct WORDDICT* son;
} WordDictionary;
WordDictionary* wordDictionaryCreate();
void wordDictionaryAddWord(WordDictionary* obj, char* word);
bool wordDictionarySearch(WordDictionary* obj, char* word);
void wordDictionaryFree(WordDictionary* obj);
// 1-4.cpp: 定义控制台应用程序的入口点。
//
/*设计一个支持以下两种操作的数据结构：??

void addWord(word)
bool search(word)
search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 . 可以表示任何一个字母。

示例:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
说明:

你可以假设所有单词都是由小写字母 a-z 组成的da
*/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "1-4.h"

WordDictionary* wordDictionaryCreate() {
	WordDictionary* rs;
	rs = (WordDictionary*)malloc(sizeof(WordDictionary));
	rs->isword = 0;
	rs->bro = NULL;
	rs->son = NULL;
	return rs;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary* obj, char* word) {
	WordDictionary* temp, *rs;
	WordDictionary* betemp=NULL;
	char str, *pt;
	int flag;
	flag = 0;
	temp = obj;
	pt = word;

	while ((str = *pt) != '\0'&&temp->son != NULL)
	{
		flag = 0;
		temp = temp->son;

		while (temp != NULL)
		{
			if (temp->c == str)
			{
				flag = 1;
				pt++;
				break;
			}
			else
			{
				betemp = temp;
				temp = temp->bro;
			}				
		}
		if (flag == 0 && betemp != NULL)
		{
			rs = wordDictionaryCreate();
			rs->c = str;
			betemp->bro = rs;
			temp = betemp->bro;
			pt++;
			betemp = NULL;
			break;
		}

	
	}
	while ((str = *pt) != '\0')
	{
		rs = wordDictionaryCreate();
		rs->c = str;
		temp->son =rs;
		temp = temp->son;
		pt++;
	}
	temp->isword = 1;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char* word) {
	WordDictionary* temp;
	char str, *pt;
	int flag;
	flag = 0;
	temp = obj;
	pt = word;

	if ((str = *pt) != '\0')
	{
		if (temp->son != NULL)
		{
			flag = 0;
			temp = temp->son;
			if (str != '.')
			{
				while (temp != NULL)
				{
					if (temp->c == str)
					{
						pt++;
						flag = 1;
						break;
					}
					temp = temp->bro;
				}
				if (flag == 0)
					return 0;//当层没找到
				else
				{
					if (wordDictionarySearch(temp, pt))
						return 1;
					else
						return 0;
				}
			}
			else
			{
				pt++;
				while (temp != NULL)
				{
					if (*pt == '\0'&&temp->isword==1)
						return 1;
					if (wordDictionarySearch(temp, pt))
						return 1;
					else
						temp = temp->bro;
				}
				return 0;
			}
		}
		else
			return 0;//当层应当有字符，但当层为空
	}
	else
		return temp->isword;

}

void wordDictionaryFree(WordDictionary* obj) {
	if (obj->son != NULL)
		wordDictionaryFree(obj->son);
	if (obj->bro != NULL)
		wordDictionaryFree(obj->bro);
	free(obj);
}


/**
* Your WordDictionary struct will be instantiated and called as such:
* struct WordDictionary* obj = wordDictionaryCreate();
* wordDictionaryAddWord(obj, word);
* bool param_2 = wordDictionarySearch(obj, word);
* wordDictionaryFree(obj);
*["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
*[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
*/
int main()
{
	char word1[] = "ran";
	char word2[] = "rune";
	char word3[]= "runner";
	char word4[] = "runs";
	char word5[] = "add";
	char word6[] = "adds";
	char word7[] = "adder";
	char word8[] = "addee";
	char w1[] = "add.";
	//char w3[] = "bad";
	//char w2[] = ".ad";
	WordDictionary* obj = wordDictionaryCreate();
	wordDictionaryAddWord(obj, word1);
	wordDictionaryAddWord(obj, word2);
	wordDictionaryAddWord(obj, word3);
	wordDictionaryAddWord(obj, word4);
	wordDictionaryAddWord(obj, word5);
	wordDictionaryAddWord(obj, word6);
	wordDictionaryAddWord(obj, word7);
	wordDictionaryAddWord(obj, word8);

	bool param_1 = wordDictionarySearch(obj, w1);
	
	//bool param_2 = wordDictionarySearch(obj, w2);
	//bool param_3 = wordDictionarySearch(obj, w3);
	//bool param_4 = wordDictionarySearch(obj, &"b..");
	// printf("%d %d %d %d",param_1,param_2,param_3,param_4);
	printf("%d\n", param_1);
	system("pause");
	wordDictionaryFree(obj);
	return 0;
}


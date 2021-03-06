// 2-2.cpp: 定义控制台应用程序的入口点。
/*
给定一个二维网格 board 和一个字典中的单词列表 words，找出所有同时在二维网格和字典中出现的单词。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。
示例:
输入:
words = ["oath","pea","eat","rain"] and board =
[
['o','a','a','n'],
['e','t','a','e'],
['i','h','k','r'],
['i','f','l','v']
]

输出: ["eat","oath"]
说明:
你可以假设所有输入都由小写字母 a-z 组成。
提示:
你需要优化回溯算法以通过更大数据量的测试。你能否早点停止回溯？
如果当前单词不存在于所有单词的前缀中，则可以立即停止回溯。什么样的数据结构可以有效地执行这样的操作？散列表是否可行？为什么？ 前缀树如何？如果你想学习如何实现一个基本的前缀树，请先查看这个问题： 实现Trie（前缀树）。

*/
#include "stdafx.h"


int main()
{
	vector<vector<char>> board;
	
	vector<char> temp;
	vector<string> words;
	vector<string> rs;
	int i = 0;
	//words.push_back("oath");
	//words.push_back("pea");
	//words.push_back("eat");
	//words.push_back("rain");
	//char d1[4] = { 'o','a','a','n' };
	//for (i = 0; i < 4; i++)
	//	temp.push_back(d1[i]);
	//board.push_back(temp);
	//temp.clear();
	//char d2[4] = { 'e','t','a','e' };
	//for (i = 0; i < 4; i++)
	//	temp.push_back(d2[i]);
	//board.push_back(temp);
	//temp.clear();
	//char d3[4] = { 'i','h','k','r' };
	//for (i = 0; i < 4; i++)
	//	temp.push_back(d3[i]);
	//board.push_back(temp);
	//temp.clear();
	char d4[2] = { 'a','a'};
	for (i = 0; i < 2; i++)
		temp.push_back(d4[i]);
	board.push_back(temp);
	temp.clear();

	words.push_back("a");

	rs=findWords(board, words);
    return 0;
}

int finds(string str, int* flag, int n, int m, vector<vector<char>>& board)
{
	char c;
	int rowboard, colboard;
	int ans = 0;
	//vector<vector<char>> board = Board;
	if (str.length() > 0)
	{
		rowboard = board.size();
		colboard = board.at(0).size();
		c = str.at(0);
		if (!ans&&m < colboard - 1)
		{
			if ((!flag[n*colboard + m + 1]) && c == board.at(n).at(m + 1))
			{
				m = m + 1;
				flag[n*colboard + m] = 1;
				ans = 1;
			}

		}
		if (!ans&&m > 0)
		{
			if ((!flag[n*colboard + m - 1]) && c == board.at(n).at(m - 1))
			{
				m = m - 1;
				flag[n*colboard + m] = 1;
				ans = 1;
			}
		}
		if (!ans&&n>0)
		{
			if ((!flag[(n - 1)*colboard + m]) && c == board.at(n).at(m))
			{
				n = n - 1;
				flag[n*colboard + m] = 1;
				ans = 1;
			}
		}
		if (!ans&&n < rowboard - 1)
		{
			if ((!flag[(n + 1)*colboard + m]) && c == board.at(n + 1).at(m))
			{
				n = n + 1;
				flag[n*colboard + m] = 1;
				ans = 1;
			}
		}
		if (ans)
		{
			return finds(str.substr(1, str.length()), flag, n, m, board);
		}
		else
			return 0;
	}
	else
	{
		return 1;
	}
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
{
	char c;
	string str;
	vector<string> rs;
	int rowboard, colboard, lenword;
	int i, j;
	int m, n;//记录当前位置
	int ans;//指示是否已经找到结果
	rowboard = board.size();
	colboard = board.at(0).size();
	int* flag=new int[rowboard*colboard];
	lenword = words.size();
	for (i = 0; i <lenword; i++)
	{
		str = words.at(i);
		m = 0;
		n = 0;
		ans = 0;
		//第一位，遍历整个board
		c = str.at(0);
		for (n = 0; n < rowboard&&!ans; n++)
		{
			for (m = 0; m < colboard&&!ans; m++)
			{
				if (board.at(n).at(m) == c)
				{
					memset(flag, 0, rowboard*colboard * sizeof(int));
					flag[n*colboard + m] = 1;
					//递归找结果
					ans=finds(str.substr(1, str.length()), flag, n, m, board);
					if (ans)
						rs.push_back(words.at(i));
				}
			}
		}
	}

	return rs;
}


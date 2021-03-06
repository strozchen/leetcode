// 2-1.cpp: 定义控制台应用程序的入口点。
/*
	数组中两个数的最大异或值
	给定一个非空数组，数组中元素为 a0, a1, a2, … , an-1，其中 0 ≤ ai < 231 。
	找到 ai 和aj 最大的异或 (XOR) 运算结果，其中0 ≤ i,  j < n 。
	你能在O(n)的时间解决这个问题吗？
	示例:
	输入: [3, 10, 5, 25, 2, 8]
	输出: 28
	解释: 最大的结果是 5 ^ 25 = 28.
*/
#include "stdafx.h"
#include "2-1.h"
#include <stdlib.h>

#define LEN 31

void insert(Node* obj, int in)
{
	int i;
	int flag;
	Node* temp;
	Node* newNode;
	temp = obj;
	for (i = LEN; i>= 0; i--)
	{
		flag = (in & (1 << i))?1:0;
		if (temp->next[flag] == NULL)
		{
			newNode = (Node*)malloc(sizeof(Node));
			newNode->next[0] = NULL;
			newNode->next[1] = NULL;
			temp->next[flag] = newNode;	
		}
		temp = temp->next[flag];
	}
}


void treeFree(Node* tree)
{
	int i;
	if (tree != NULL)
	{
		if (tree->next[0] != NULL)
			treeFree(tree->next[0]);
		if (tree->next[1] != NULL)
			treeFree(tree->next[1]);
		free(tree);
	}
	else
		return;
	
	
}

int findMaximumXOR(int* nums, int numsSize) {
	int i,pt;
	int flag=0;
	int sum,max;
	Node* tree;
	Node* temp;
	tree = (Node*)malloc(sizeof(Node));
	tree->next[0] = NULL;
	tree->next[1] = NULL;
	max = 0;

	for ( i = 0; i < numsSize; i++)
	{
		insert(tree, nums[i]);
	}

	for (pt = 0; pt < numsSize; pt++)
	{
		sum = 0;
		temp = tree;
		for (i = LEN; i >= 0; i--)
		{
			flag = (nums[pt]&(1 << i))?0:1;

			if (temp->next[flag] != NULL)
			{
				sum = sum | (1 << i);
				temp = temp->next[flag];
			}
			else
				temp = temp->next[1 - flag];
		}
		max = (max > sum) ? max : sum;
	}
	treeFree(tree);
	return max;
}

int main()
{
	int nums[] = { 3,10,5,25,2,8 };
	int numsSize=sizeof(nums)/sizeof(int);
	int rs=0;
	rs=findMaximumXOR(nums, numsSize);
	printf("%d", rs);
	getchar();
	
    return 0;
}


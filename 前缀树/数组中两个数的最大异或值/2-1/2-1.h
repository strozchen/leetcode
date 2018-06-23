#pragma once
typedef struct NODE
{
	struct NODE* next[2];
	NODE()
	{
		next[0] = nullptr;
		next[1] = nullptr;
	}
}Node;

void insert(Node* obj, int in);
int findMaximumXOR(int* nums, int numsSize);
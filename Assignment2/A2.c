#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct StackNode
{
	char url[50];
	struct StackNode* next;
} StackNode;

typedef struct Stack
{
	StackNode* top;
} Stack;

typedef struct QueueNode
{
	char url[50];
	struct QueueNode* next;
} QueueNode;

typedef struct Queue
{
	QueueNode* front;
	QueueNode* rear;
} Queue;

int main(void)
{

	Stack backStack = { NULL };
	Stack forwardStack = { NULL };
	Queue historyQueue = { NULL, NULL };

	return 0;
}
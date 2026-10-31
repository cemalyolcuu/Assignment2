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

StackNode* createStackNode(char* url)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));

	if (newNode == NULL)
	{
		return NULL;
	}
	strcpy_s(newNode->url, sizeof(newNode->url), url);
	newNode->next = NULL;

	return newNode;
}

void push(Stack* stack, char* newUrl)
{
	StackNode* newNode = createStackNode(newUrl);

	if (newNode == NULL)
	{
		printf("Memory allocation failed.\n");
		return;
	}

	newNode->next = stack->top;
	stack->top = newNode;
}

bool isStackEmpty(Stack* stack)
{
	return stack->top == NULL;
}

char* peekStack(Stack* stack)
{
	if (isStackEmpty(stack))
	{
		return NULL;
	}

	return stack->top->url;
}

char* pop(Stack* stack)
{
	if (isStackEmpty(stack))
	{
		return NULL;
	}

	StackNode* temp = stack->top;

	char* url = (char*)malloc(strlen(temp->url) + 1);

	if (url == NULL)
	{
		return NULL;
	}

	strcpy_s(url, strlen(temp->url) + 1, temp->url);

	stack->top = temp->next;

	free(temp);

	return url;
}

QueueNode* createQueueNode(char* url)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	
	if (newNode == NULL)
	{
		return NULL;
	}

	if (strlen(url) >= sizeof(newNode->url))
	{
		free(newNode);
		return NULL;
	}
	strcpy_s(newNode->url, sizeof(newNode->url), url);
	newNode->next = NULL;

	return newNode;
}

void enqueue(Queue* queue, char* newUrl)
{
	QueueNode* newNode = createQueueNode(newUrl);
	if (newNode == NULL)
	{
		printf("Cannot add URL to queue.\n");
		return;
	}
	if (queue->front == NULL)
	{
		queue->front = newNode;
		queue->rear = newNode;
	}
	else
	{
		queue->rear->next = newNode;
		queue->rear = newNode;
	}
}

int main(void)
{
	Stack backStack = { NULL };
	Stack forwardStack = { NULL };
	Queue historyQueue = { NULL, NULL };

	

	return 0;
}
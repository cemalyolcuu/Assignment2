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


bool isQueueEmpty(Queue* queue)
{
	return queue->front == NULL;
}

char* peekQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		return NULL;
	}

	return queue->front->url;
}

char* dequeue(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		return NULL;
	}

	QueueNode* temp = queue->front;

	char* url = (char*)malloc(strlen(temp->url) + 1);

	if (url == NULL)
	{
		return NULL;
	}

	strcpy_s(url, strlen(temp->url) + 1, temp->url);

	queue->front = temp->next;

	if (queue->front == NULL)
	{
		queue->rear = NULL;
	}

	free(temp);

	return url;
}


int main(void)
{
    Stack backStack = { NULL };
    Stack forwardStack = { NULL };
    Queue historyQueue = { NULL, NULL };

    int choice;
    int ch;
    char url[50];
    char* removedUrl;
    char* currentPage;

    while (1)
    {
        printf("\nBrowser History Manager\n");
        printf("1. Visit New Web Page\n");
        printf("2. Navigate Backward\n");
        printf("3. Navigate Forward\n");
        printf("4. Display Current Page\n");
        printf("5. Browsing History Log (using Queue)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf_s("%d", &choice) != 1)
        {
            printf("Invalid input.\n");

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }

            if (ch == EOF)
            {
                break;
            }

            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        switch (choice)
        {
        case 1:
            printf("Enter URL: ");

            if (fgets(url, sizeof(url), stdin) == NULL)
            {
                break;
            }

            url[strcspn(url, "\n")] = '\0';

            if (strlen(url) == 0)
            {
                printf("URL cannot be empty.\n");
                break;
            }

            /* Clear forward stack when visiting a new page */
            while (!isStackEmpty(&forwardStack))
            {
                removedUrl = pop(&forwardStack);

                if (removedUrl == NULL)
                {
                    break;
                }

                free(removedUrl);
            }

            push(&backStack, url);
            enqueue(&historyQueue, url);

            printf("Page visited: %s\n", url);
            break;

        case 2:
            printf("Backward navigation will be added next.\n");
            break;

        case 3:
            printf("Forward navigation will be added next.\n");
            break;

        case 4:
            currentPage = peekStack(&backStack);

            if (currentPage == NULL)
            {
                printf("No current page.\n");
            }
            else
            {
                printf("Current page: %s\n", currentPage);
            }
            break;

        case 5:
            printf("Browsing history will be added later.\n");
            break;

        case 6:
            printf("Exiting browser.\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }

        if (choice == 6)
        {
            break;
        }
    }

    /* Free back stack */
    while (!isStackEmpty(&backStack))
    {
        removedUrl = pop(&backStack);

        if (removedUrl == NULL)
        {
            break;
        }

        free(removedUrl);
    }

    /* Free forward stack */
    while (!isStackEmpty(&forwardStack))
    {
        removedUrl = pop(&forwardStack);

        if (removedUrl == NULL)
        {
            break;
        }

        free(removedUrl);
    }

    /* Free history queue */
    while (!isQueueEmpty(&historyQueue))
    {
        removedUrl = dequeue(&historyQueue);

        if (removedUrl == NULL)
        {
            break;
        }

        free(removedUrl);
    }

    return 0;
}
/*
 * FILE        : A2.c
 * PROJECT     : Data Structures, Assignment 2
 * PROGRAMMER  : Cemal Yolcu
 * FIRST VERSION : 2026-10-30
 * DESCRIPTION :
 *     This program is a simple browser history manager.
 *     It uses two stacks for backward and forward navigation
 *     and a queue to store browsing history.
 *     The user can visit pages, navigate backward and forward,
 *     display the current page, and view browsing history.
 *     The program uses linked lists and dynamic memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

 /* A node stores a URL and a pointer to the next stack node. */
typedef struct StackNode
{
	char url[50];
	struct StackNode* next;
} StackNode;

/* The stack keeps a pointer to the top node. */
typedef struct Stack
{
	StackNode* top;
} Stack;

/* A queue node stores a URL and a pointer to the next node. */
typedef struct QueueNode
{
	char url[50];
	struct QueueNode* next;
} QueueNode;

/* The queue keeps pointers to the front and rear nodes. */
typedef struct Queue
{
	QueueNode* front;
	QueueNode* rear;
} Queue;

/*
 * FUNCTION    : createStackNode
 * DESCRIPTION :
 *     Creates a new stack node using malloc.
 *     Copies the URL into the node.
 * RETURNS     :
 *     A pointer to the new node, or NULL if it fails.
 */
StackNode* createStackNode(char* url)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));

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

/*
 * FUNCTION    : push
 * DESCRIPTION :
 *     Adds a new URL to the top of the stack.
 * RETURNS     :
 *     True if successful, otherwise false.
 */
bool push(Stack* stack, char* newUrl)
{
    StackNode* newNode = createStackNode(newUrl);

    if (newNode == NULL)
    {
        return false;
    }

    newNode->next = stack->top;
    stack->top = newNode;

    return true;
}

/*
 * FUNCTION    : isStackEmpty
 * DESCRIPTION :
 *     Checks if the stack is empty.
 * RETURNS     :
 *     True if empty, otherwise false.
 */
bool isStackEmpty(Stack* stack)
{
	return stack->top == NULL;
}

/*
 * FUNCTION    : peekStack
 * DESCRIPTION :
 *     Returns the top URL without removing the node.
 * RETURNS     :
 *     The top URL, or NULL if the stack is empty.
 */
char* peekStack(Stack* stack)
{
	if (isStackEmpty(stack))
	{
		return NULL;
	}

	return stack->top->url;
}

/*
 * FUNCTION    : pop
 * DESCRIPTION :
 *     Removes the top node from the stack.
 *     Returns a copy of the URL and frees the node.
 * RETURNS     :
 *     A new URL string, or NULL if it fails.
 *     The returned string must be freed by the caller.
 */
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

/*
 * FUNCTION    : createQueueNode
 * DESCRIPTION :
 *     Creates a new queue node using malloc.
 *     Stores the URL and sets next to NULL.
 * RETURNS     :
 *     A pointer to the new node, or NULL if it fails.
 */
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

/*
 * FUNCTION    : enqueue
 * DESCRIPTION :
 *     Adds a new URL to the rear of the queue.
 * RETURNS     :
 *     True if successful, otherwise false.
 */
bool enqueue(Queue* queue, char* newUrl)
{
    QueueNode* newNode = createQueueNode(newUrl);

    if (newNode == NULL)
    {
        return false;
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

    return true;
}

/*
 * FUNCTION    : isQueueEmpty
 * DESCRIPTION :
 *     Checks if the queue is empty.
 * RETURNS     :
 *     True if empty, otherwise false.
 */
bool isQueueEmpty(Queue* queue)
{
	return queue->front == NULL;
}

/*
 * FUNCTION    : peekQueue
 * DESCRIPTION :
 *     Returns the front URL without removing it.
 * RETURNS     :
 *     The front URL, or NULL if the queue is empty.
 */
char* peekQueue(Queue* queue)
{
	if (isQueueEmpty(queue))
	{
		return NULL;
	}

	return queue->front->url;
}

/*
 * FUNCTION    : dequeue
 * DESCRIPTION :
 *     Removes the front node from the queue.
 *     Returns a copy of the URL and frees the node.
 * RETURNS     :
 *     A new URL string, or NULL if it fails.
 *     The returned string must be freed by the caller.
 */
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

/*
 * FUNCTION    : displayHistory
 * DESCRIPTION :
 *     Starts from the front of the queue.
 *     Displays all URLs in the browsing history.
 * RETURNS     :
 *     void
 */
void displayHistory(Queue* queue)
{
	QueueNode* current = queue->front;

    if (isQueueEmpty(queue))
    {
        printf("Browsing history is empty.\n");
		return;
    }

	printf("Browsing History:\n");

    while (current != NULL)
    {
        printf("%s\n", current->url);
        current = current->next;
    }
}

/*
 * FUNCTION    : moveToRear
 * DESCRIPTION :
 *     Searches for the last matching URL in the queue.
 *     Moves that node to the rear by changing pointers.
 *     Does not create a new node.
 * RETURNS     :
 *     void
 */
void moveToRear(Queue* queue, char* url)
{
    QueueNode* current = queue->front;
    QueueNode* previous = NULL;
    QueueNode* found = NULL;
    QueueNode* foundPrevious = NULL;

    while (current != NULL)
    {
        if (strcmp(current->url, url) == 0)
        {
            found = current;
            foundPrevious = previous;
        }

        previous = current;
        current = current->next;
    }

    if (found == NULL)
    {
        return;
    }

    if (found == queue->rear)
    {
        return;
    }

    if (foundPrevious == NULL)
    {
        queue->front = found->next;
    }
    else
    {
        foundPrevious->next = found->next;
    }

    queue->rear->next = found;
    queue->rear = found;
    found->next = NULL;
}

/*
 * FUNCTION    : removeTopNode
 * DESCRIPTION :
 *     Removes the top stack node.
 *     Frees the node without creating a new URL copy.
 * RETURNS     :
 *     void
 */
void removeTopNode(Stack* stack)
{
    if (stack->top == NULL)
    {
        return;
    }

    StackNode* temp = stack->top;

    stack->top = temp->next;

    free(temp);
}

/*
 * FUNCTION    : removeFrontNode
 * DESCRIPTION :
 *     Removes the front queue node.
 *     Updates front and rear pointers.
 *     Frees the removed node.
 * RETURNS     :
 *     void
 */
void removeFrontNode(Queue* queue)
{
    if (queue->front == NULL)
    {
        return;
    }

    QueueNode* temp = queue->front;

    queue->front = temp->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
}

/*
 * FUNCTION    : main
 * DESCRIPTION :
 *     Initializes the stacks and queue.
 *     Displays the browser menu and handles user choices.
 *     Frees all allocated nodes before exiting.
 * RETURNS     :
 *     0 when the program finishes normally.
 */
int main(void)
{
    Stack backStack = { NULL };
    Stack forwardStack = { NULL };
    Queue historyQueue = { NULL, NULL };

    int choice;
    int ch;
    char url[50];
    char* currentPage;

    while (1) /* Keep showing the menu until the user exits */
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

        switch (choice) /* Run the operation selected by the user */
        {
        case 1: /* Visit a new page */
            printf("Enter URL: ");

            if (fgets(url, sizeof(url), stdin) == NULL)
            {
                break;
            }

            /* Check if URL is too long */
            if (strchr(url, '\n') == NULL)
            {
                ch = getchar();

                if (ch != '\n' && ch != EOF)
                {
                    while ((ch = getchar()) != '\n' && ch != EOF)
                    {
                    }

                    printf("URL is too long.\n");
                    break;
                }
            }

            url[strcspn(url, "\n")] = '\0';

            if (strlen(url) == 0)
            {
                printf("URL cannot be empty.\n");
                break;
            }

            /* Add URL to back stack */
            if (!push(&backStack, url))
            {
                printf("Cannot visit page. Memory allocation failed.\n");
                break;
            }

            /* Add URL to history queue */
            if (!enqueue(&historyQueue, url))
            {
                removeTopNode(&backStack);
                printf("Cannot visit page. Memory allocation failed.\n");
                break;
            }

            /* Clear forward stack after successful visit */
            while (!isStackEmpty(&forwardStack))
            {
                removeTopNode(&forwardStack);
            }

            printf("Page visited: %s\n", url);
            break;

        case 2: /* Navigate backward using stacks */
            if (isStackEmpty(&backStack) || backStack.top->next == NULL)
            {
                printf("No previous page.\n");
            }
            else
            {
                currentPage = peekStack(&backStack);

                if (push(&forwardStack, currentPage))
                {
                    removeTopNode(&backStack);

                    currentPage = peekStack(&backStack);

                    moveToRear(&historyQueue, currentPage);

                    printf("Current page: %s\n", currentPage);
                }
                else
                {
                    printf("Cannot go back. Memory allocation failed.\n");
                }
            }
            break;

        case 3: /* Navigate forward using stacks */
            if (isStackEmpty(&forwardStack))
            {
                printf("No forward page.\n");
            }
            else
            {
                currentPage = peekStack(&forwardStack);

                if (push(&backStack, currentPage))
                {
                    removeTopNode(&forwardStack);

                    currentPage = peekStack(&backStack);

                    moveToRear(&historyQueue, currentPage);

                    printf("Current page: %s\n", currentPage);
                }
                else
                {
                    printf("Cannot go forward. Memory allocation failed.\n");
                }
            }
            break;

        case 4: /* Display the current page */
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

        case 5: /* Display browsing history using the queue */
			displayHistory(&historyQueue);
            break;

        case 6: /* Exit the browser */
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
        removeTopNode(&backStack);
    }

    /* Free forward stack */
    while (!isStackEmpty(&forwardStack))
    {
        removeTopNode(&forwardStack);
    }

    /* Free history queue */
    while (!isQueueEmpty(&historyQueue))
    {
        removeFrontNode(&historyQueue);
    }

    return 0;
}
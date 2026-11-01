# Assignment 2 - Browser History Manager

**Name:** Cemal Yolcu  
**Course:** Data Structures  
**Language:** C

## Description

For this assignment, I created a simple browser history program using C.

The program allows the user to visit websites, go back to previous pages, go forward, and check the browsing history.

I used two stacks and one queue with linked lists to make this program.

## How the Program Works

I used two stacks for the back and forward pages.

When the user visits a new website, the URL is added to the back stack. If the user goes back, the current page moves to the forward stack.

The queue is used to keep the browsing history. When the user goes back or forward, the matching URL is moved to the end of the queue.

## Menu Options

1. Visit New Web Page
2. Navigate Backward
3. Navigate Forward
4. Display Current Page
5. Browsing History Log
6. Exit

## Example

If I choose option 1 and enter google, the program shows:

Page visited: google

If I choose option 4, it shows:

Current page: google

If I visit youtube and choose option 2, it goes back to google.

## Memory and Input Checks

I used malloc() to create new nodes and free() to remove them.

The program also checks for invalid menu choices, empty URLs, and URLs that are too long.

Before the program ends, the remaining nodes in the stacks and queue are freed.

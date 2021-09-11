/*
    Author: Cameron Ellis
    Purpose: Priority Queue Header File
    Date: 10/24/2020
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void* object;
    float priority;
    struct node* next;
} Node;

typedef struct queue {
    Node *head;
    int queueLength;
    int minmax;
} PQueueInfo;

typedef struct pqueue{
    PQueueInfo *pqueueInfo;
} PQueue;


/* This function initializes the priority queue.The first parameter specifies
whether objects will bere turned in ascending or descending order by priority.
A negative number implies ascending while a non negative number implies
descending. The second parameter is an error code
(the values of which must of course always be documented).*/
PQueue initPQueue(int minmax, int* eCode);

/* This function inserts obj with its associated
priority given by the second parameter.*/
void insertPQ(void* obj, float priority, PQueue q, int* eCode);

/* This function removes and returns the next
object in priority order in O(1) time.*/
void* deletePQ(PQueue q);

/* This function returns the priority of the next
object to be removed in O(1) time*/
float getPriority(PQueue q);

/* This function returns the number of object sin the
priority queue in O(1) time.*/
int getSizePQ(PQueue q);

/* This function frees all memory associated with the priority queue.
Documentation should explicitly inform the user to not attempt to use the PQ
after calling this function. */
void freePQ(PQueue q);

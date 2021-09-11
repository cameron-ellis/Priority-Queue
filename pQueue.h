/*
    Author: Cameron Ellis
    Purpose: pQueue Header File
    Date: 10/24/2020
*/

#include <stdio.h>
#include <stdlib.h>

//Priority Node Data Type
typedef struct pnode {
    void* object;
    float priority;
    struct pnode* next;
} PNode;

//Priority Queue Data Type
typedef struct pqueue {
    PNode* head;
    int* queueSize;
    int minmax;
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

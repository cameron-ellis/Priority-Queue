/*
    Author: Cameron Ellis
    Purpose: pQueue implementation file
    Date: 10/24/2020
*/

#include "pQueue.h"

/*
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
*/

/*
    Helper functions
*/
//Function to create a PNode
PNode * createPNode(void* obj, float priority) {
    PNode* p = malloc(sizeof(PNode));
    p->object = obj;
    p->priority = priority;
    p->next = NULL;
    return p;
}

/*
    Implementation Functions
*/

/* This function initializes the priority queue.The first parameter specifies
whether objects will bere turned in ascending or descending order by priority.
A negative number implies ascending while a non negative number implies
descending. The second parameter is an error code
(the values of which must of course always be documented).*/
PQueue initPQueue(int minmax, int* eCode) {
    if (minmax == 0) {
        *eCode = -1; //minmax needs to be positive or negative number
        PQueue userQ; //return empty PQueue to user
        userQ.head = NULL; //to make sure no segfaults in code
        userQ.minmax = 0; //for later on error checking
        *userQ.queueSize = 0; //make size zero since nothing will be held in it
        return userQ;
    }
    else {
        *eCode = 0; //minmax needs to be positive or negative number
        PQueue userQ;
        userQ.head = malloc(sizeof(PNode)); //allocate memory for dummy node
        userQ.head->object = NULL; //set object for dummy node to NULL
        userQ.head->priority = 0; //set priority to 0, though it won't be needed
        userQ.head->next = NULL; //set start of queue to NULL
        userQ.queueSize = malloc(sizeof(int));  //allocate memory to queueSize
        *userQ.queueSize = 0; //set queueSize to zero at start
        userQ.minmax = minmax; //set minmax
        return userQ;
    }
}

/* This function inserts obj with its associated
priority given by the second parameter.*/
void insertPQ(void* obj, float priority, PQueue q, int* eCode) {
    PNode* p = q.head; //This pointer will be used to scan through list
    if (obj == NULL) {
        *eCode = -1; //object must be non-NULL
    }
    //Insertion algorithm for a min queue
    else if (q.minmax < 0) {
        PNode * objIn = createPNode(obj,priority);
        while (p->next != NULL) {
            /*If next priority is greater than or equal to the passed Priority
              then insert our object before it*/
            if (p->next->priority >= priority) {
                objIn->next = p->next;
                p->next = objIn;
                (*q.queueSize)++; //increment queue size
                *eCode = 0; //successful insertion
                return;
            }
            else {
                p = p->next; //if passed priority is greater, move to next
            }
        }
        /*If we start off list NULL or go through list and passed priority
        is the largest, we insert at location of p->next */
        p->next = objIn;
        (*q.queueSize)++;
        *eCode = 0;
        return;
    }
    //Insertion algorithm for max queue
    else if (q.minmax > 0) {
        PNode * objIn = createPNode(obj,priority);
        while (p->next != NULL) {
            /*If next priority is less than or equal to the passed Priority
              then insert our object before it*/
            if (p->next->priority <= priority) {
                objIn->next = p->next;
                p->next = objIn;
                (*q.queueSize)++; //increment queue size
                *eCode = 0; //successful insertion
                return;
            }
            else {
                p = p->next; //if passed priority is smaller, move to next
            }
        }
        /*If we start off list NULL or go through list and passed priority
        is the smallest, we insert at location of p->next */
        p->next = objIn;
        (*q.queueSize)++; //increment size
        *eCode = 0;
        return;
    }
    //If minmax of priority queue is equal to 0
    else {
        *eCode = -2; //Invalid priority queue
    }
}

/* This function removes and returns the next
object in priority order in O(1) time.*/
void* deletePQ(PQueue q) {
    if (q.minmax == 0) {
        return NULL; //invalid queue type entered
    }
    else if (q.head->next == NULL) {
        return NULL; //queue is empty return NULL
    }
    else {
        PNode* delete = q.head->next; //get the priority node at head to delete
        PNode* newPriority = q.head->next->next; //get the next priority node
        q.head->next = newPriority; //make the next priority the new head
        free(delete); //delete the priority node
        (*q.queueSize)--; //decrement size of queue
        if (newPriority == NULL) {
            return NULL;
        }
        else {
            return newPriority->object; //return the object of the next priority node
        }
    }
}

/* This function returns the priority of the next
object to be removed in O(1) time*/
float getPriority(PQueue q) {
    if (q.minmax == 0) {
        return -1; //invalid queue type entered
    }
    else if (q.head->next == NULL) {
        return -2; //queue is empty
    }
    else {
        PNode* priorityNode = q.head->next; //get priority Node from head
        float priority = priorityNode->priority; //get priority value from it
        return priority; //return priority value
    }
}

/* This function returns the number of object sin the
priority queue in O(1) time.*/
int getSizePQ(PQueue q) {
    int qSize = *q.queueSize; //get queue size and store in int
    return qSize; //return size to user
}

/* This function frees all memory associated with the priority queue.
Documentation should explicitly inform the user to not attempt to use the PQ
after calling this function. */
void freePQ(PQueue q) {
    PNode *del, *nxt; //hold the PNode to delete, and the next PNode
    del = q.head;
    //Free all memory allocated to PNodes
    while (del != NULL) {
        nxt = del->next;
        free(del);
        del = nxt;
    }
    //Free memory allocated to queueSize
    free(q.queueSize);
    return;
}

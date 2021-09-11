/*
    Author: Cameron Ellis
    Purpose: Priority Queue Implementation File
    Date: 10/24/2020
*/

#include "priorityQueue.h"


/***** Function to create a PNode *****/
Node * createNode(void* obj, float priority) {
    Node* p = malloc(sizeof(Node));
    if (p == NULL) {
        return NULL;  //if malloc fails
    }
    p->object = obj;
    p->priority = priority;
    p->next = NULL;
    return p;
}

/************************ PRIORITY QUEUE FUNCTIONS ************************/

/* This function initializes the priority queue.The first parameter specifies
whether objects will bere turned in ascending or descending order by priority.
A negative number implies ascending while a non negative number implies
descending. The second parameter is an error code
(the values of which must of course always be documented).*/
PQueue initPQueue(int minmax, int* eCode) {
    if (minmax == 0) {
        *eCode = -1; //minmax needs to be positive or negative number
        PQueue userQ;
        userQ.pqueueInfo = NULL;
        return userQ; //return an empty queue to the user
    }
    else {
        *eCode = 0; //minmax was within range, so create PQueue
        PQueue userQ;
        userQ.pqueueInfo = malloc(sizeof(PQueueInfo));
        if (userQ.pqueueInfo == NULL) {
            *eCode = -2; //memory could not be allocated to pqueueInfo
            return userQ;
        }
        userQ.pqueueInfo->head = malloc(sizeof(Node)); //allocate memory for dummy node
        if (userQ.pqueueInfo->head == NULL) {
            *eCode = -2; //memory could not be allocated for queue
            return userQ;
        }
        userQ.pqueueInfo->head->object = NULL; //set object for dummy node to NULL
        userQ.pqueueInfo->head->priority = 0; //set priority to 0, though it won't be needed
        userQ.pqueueInfo->head->next = NULL; //set start of queue to NULL
        userQ.pqueueInfo->queueLength = 0; //set queueSize to zero at start
        userQ.pqueueInfo->minmax = minmax; //set minmax
        return userQ;
    }
}

/* This function inserts obj with its associated
priority given by the second parameter.*/
void insertPQ(void* obj, float priority, PQueue q, int* eCode) {
    if (q.pqueueInfo == NULL) {
        *eCode = -2; //Invalid priority queue
        return;
    }
    else if (obj == NULL) {
        *eCode = -1; //object must be non-NULL
        return;
    }
    //Insertion algorithm for a min queue
    else if (q.pqueueInfo->minmax < 0) {
        Node* p = q.pqueueInfo->head; //This pointer will be used to scan through list
        if (p == NULL) {
            *eCode = -4; //memory was not allocated for queue
            return;
        }
        Node * objIn = createNode(obj,priority);
        if (objIn == NULL) {
            *eCode = -3; //memory could not be allocated to create Node
            return;
        }
        while (p->next != NULL) {
            /*If next priority is greater than or equal to the passed Priority
              then insert our object before it*/
            if (p->next->priority >= priority) {
                objIn->next = p->next;
                p->next = objIn;
                q.pqueueInfo->queueLength++; //increment queue size
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
        q.pqueueInfo->queueLength++;
        *eCode = 0;
        return;
    }
    //Insertion algorithm for max queue
    else if (q.pqueueInfo->minmax > 0) {
        Node* p = q.pqueueInfo->head; //This pointer will be used to scan through list
        if (p == NULL) {
            *eCode = -4; //memory was not allocated for queue
            return;
        }
        Node * objIn = createNode(obj,priority);
        if (objIn == NULL) {
            *eCode = -3; //memory could not be allocated to create Node
            return;
        }
        while (p->next != NULL) {
            /*If next priority is less than or equal to the passed Priority
              then insert our object before it*/
            if (p->next->priority <= priority) {
                objIn->next = p->next;
                p->next = objIn;
                q.pqueueInfo->queueLength++; //increment queue size
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
        q.pqueueInfo->queueLength++; //increment queue size
        *eCode = 0;
        return;
    }
}

/* This function removes and returns the next
object in priority order in O(1) time.*/
void* deletePQ(PQueue q) {
    if (q.pqueueInfo == NULL) {
        return NULL; //queue doesn't exist to be able to delete from
    }
    else if (q.pqueueInfo->head == NULL) {
        return NULL; //memory was not allocated for queue
    }
    else if (q.pqueueInfo->head->next == NULL) {
        return NULL; //queue is empty return NULL
    }
    else {
        Node* delete = q.pqueueInfo->head->next; //get the priority node at head to delete
        Node* newPriority = q.pqueueInfo->head->next->next; //get the next priority node
        q.pqueueInfo->head->next = newPriority; //make the next priority the new head
        free(delete); //delete the priority node
        q.pqueueInfo->queueLength--; //decrement size of queue
        if (newPriority == NULL) {
            return NULL; //if last node was removed return NULL
        }
        else {
            return newPriority->object; //return the object of the next priority node
        }
    }
}

/* This function returns the priority of the next
object to be removed in O(1) time*/
float getPriority(PQueue q) {
    if (q.pqueueInfo == NULL) {
        return -1; //queue does not exist
    }
    else if (q.pqueueInfo->head == NULL) {
        return -2; //memory was not allocated for queue
    }
    else if (q.pqueueInfo->head->next == NULL) {
        return -3; //queue is empty
    }
    else {
        Node* priorityNode = q.pqueueInfo->head->next; //get priority Node from head
        float priority = priorityNode->priority; //get priority value from it
        return priority; //return priority value
    }
}

/* This function returns the number of object sin the
priority queue in O(1) time.*/
int getSizePQ(PQueue q) {
    if (q.pqueueInfo == NULL) {
        return -1; //queue does not exist
    }
    else if (q.pqueueInfo->head == NULL) {
        return -2; //memory was not allocated for queue
    }
    else {
        int qSize = q.pqueueInfo->queueLength; //get queue size and store in int
        return qSize; //return size to user
    }
}

/* This function frees all memory associated with the priority queue.
Documentation should explicitly inform the user to not attempt to use the PQ
after calling this function. */
void freePQ(PQueue q) {
    if (q.pqueueInfo == NULL) {
        return; //queue does not exist
    }
    else if (q.pqueueInfo->head == NULL) {
        return; //memory was not allocated for queue
    }
    else {
        Node *del, *nxt; //hold the PNode to delete, and the next PNode
        del = q.pqueueInfo->head;
        //Free all memory allocated to PNodes
        while (del != NULL) {
            nxt = del->next;
            free(del);
            del = nxt;
        }
        //Free memory allocated to pqueueInfo
        free(q.pqueueInfo);
        return;
    }
}

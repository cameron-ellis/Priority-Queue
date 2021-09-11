/*
    Author: Cameron Ellis
    Purpose: Main testing funciton for pQueue
    Date: 10/24/2020
*/

#include "pQueue.h"

int main() {
    int* eCode;
    *eCode = 0;
    PQueue userQ1 = initPQueue(1,eCode);
    PQueue userQ2 = initPQueue(-1,eCode);
    printf("%d\n",*eCode);

    char* prez = "Prez";
    char* vprez = "VPrez";
    char* spoh = "SPOH";
    char* prezprotemp = "PrezProTemp";
    char* secofstate = "SecOfState";

    insertPQ(spoh, 3, userQ1, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ1));
    insertPQ(secofstate, 1, userQ1, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ1));
    insertPQ(vprez, 4, userQ1, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ1));
    insertPQ(prezprotemp, 2, userQ1, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ1));
    insertPQ(prez, 5, userQ1, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ1));

    insertPQ(spoh, 3, userQ2, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ2));
    insertPQ(secofstate, 1, userQ2, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ2));
    insertPQ(vprez, 4, userQ2, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ2));
    insertPQ(prezprotemp, 2, userQ2, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ2));
    insertPQ(prez, 5, userQ2, eCode);
    printf("eCode: %d, Queue Size: %d\n",*eCode, getSizePQ(userQ2));

    for (int i = 0; i < 5; i++) {
        char* p = deletePQ(userQ1);
        printf("%s Priority: %f\n",p, getPriority(userQ1));
        printf("Queue Size: %d\n", getSizePQ(userQ1));
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        char* p = deletePQ(userQ2);
        printf("%s Priority: %f\n",p, getPriority(userQ2));
        printf("Queue Size: %d\n", getSizePQ(userQ2));
    }


    freePQ(userQ1);
    freePQ(userQ2);

    return 0;
}

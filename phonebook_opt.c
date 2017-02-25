#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
/*
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 31;
    unsigned int hash = 0;

    while(*str)
        hash = hash * seed + (*str++);

    return (hash % MAX_TABLE_SIZE);
}*/

entry *findName(char lastName[], entry *pHead)
{
    /* TODO: implement */
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e->detail = NULL;
    e = e -> pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}


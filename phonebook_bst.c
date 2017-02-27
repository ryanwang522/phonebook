#include <stdlib.h>
#include <string.h>

#include "phonebook_bst.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
int Length(entry *head)
{
    int count = 0;
    entry *current = head;

    while (current != NULL) {
        count++;
        current = current -> pNext;
    }

    return count;
}

treeNode *BuildBST(entry **headRef, int length)
{
    if (length <= 0)
        return NULL;

    treeNode *left = BuildBST(headRef, length/2);
    treeNode *root = (treeNode *) malloc(sizeof(treeNode));
    root->entry = *headRef;
    root->left = left;

    *headRef = (*headRef)->pNext;

    root->right = BuildBST(headRef, length - (length / 2 + 1));

    return root;
}

entry *findName(char lastName[], treeNode *root)
{
    treeNode *current = root;
    int result;

    while (current != NULL && (result = strcasecmp(lastName, current->entry->lastName)) != 0) {
        if (result < 0)
            current = current -> left;
        else
            current = current -> right;
    }

    if (root)
        return (current->entry);
    else
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

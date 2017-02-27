#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#define OPT 2

typedef struct __PHONE_BOOK_DETAIL_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detailEntry;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detailEntry *detail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __TREE_NODE {
    entry *entry;
    struct __TREE_NODE *right;
    struct __TREE_NODE *left;
} treeNode;

int Length(entry *head);
treeNode *BuildBST(entry **headRef, int length);
entry *findName(char lastName[], treeNode *root);
entry *append(char lastName[], entry *e);

#endif

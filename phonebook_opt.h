#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1
#define MAX_TABLE_SIZE 1024

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

typedef struct __HASH_SLOT {
    entry *data;
    struct __HASH_SLOT *sNext;
} slot;

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif

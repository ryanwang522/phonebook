#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#if OPT == 1
#define OUT_FILE "opt.txt"
entry *hashTable[MAX_TABLE_SIZE] = {NULL};
entry *tableHead[MAX_TABLE_SIZE] = {NULL};
#elif OPT == 2
#define OUT_FILE "bst.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define DICT_FILE "./dictionary/words.txt"
#define MAX_TABLE_SIZE 1024

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 31;
    unsigned int hash = 0;

    while(*str)
        hash = hash * seed + (*str++);

    return (hash % MAX_TABLE_SIZE);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;

#if OPT == 1
        unsigned int hashVal = BKDRHash(line);

        if (hashTable[hashVal] == NULL) {
            hashTable[hashVal] = (entry *) malloc(sizeof(entry));
            tableHead[hashVal] = hashTable[hashVal];
        }

        hashTable[hashVal] = append(line, hashTable[hashVal]);
#else
        e = append(line, e);
#endif
    }

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";

#ifndef OPT
    e = pHead;
#elif OPT == 2
    /* Build BST from a sorted linked-list */
    treeNode *root = BuildBST(&pHead, Length(pHead));
#else
    unsigned int hashVal = BKDRHash(input);
    e = tableHead[hashVal];
#endif

#if OPT == 2
    assert(findName(input, root) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, root)->lastName, "zyxel"));
#else
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);

#if OPT == 2
    findName(input, root);
#else
    findName(input, e);
#endif

    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    FILE *output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    if (pHead != NULL) {
        free(pHead->pNext);
        free(pHead);
    }

    return 0;
}

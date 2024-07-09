#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DEADLINE_SIZE 20
#define MAX_DESCRIPTION_SIZE 256

typedef enum {
    PENDING,
    COMPLETED,
    IGNORE_STATUS // special status to act as a "NULL" for logichandler
} Status;

typedef struct TodoNode {
    char description[MAX_DESCRIPTION_SIZE];
    char deadline[MAX_DEADLINE_SIZE];
    Status status;
    struct TodoNode* next;
} TodoNode;

TodoNode* createNode(const char* description, const char* deadline, Status status);

void appendNode(TodoNode** headNode, const char* description, const char* deadline, Status status);

void removeNode(TodoNode** headNode, int id);

void editNode(TodoNode** headNode, const char* newDescription, const char* newDeadline, Status newStatus, int id);

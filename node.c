#include "node.h"

TodoNode *createNode(const char *description, const char *deadline, Status status) {
    TodoNode *newNode = (TodoNode *)malloc(sizeof(TodoNode));
    strcpy(newNode->description, description);
    newNode->status = status;
    newNode->next = NULL;

    if (deadline != NULL) {
        strcpy(newNode->deadline, deadline);
    }
    else {
        strcpy(newNode->deadline, "");
    }

    return newNode;
}

void appendNode(TodoNode **headNode, const char *description, const char *deadline, Status status) {
    TodoNode *newNode = createNode(description, deadline, status);

    if (*headNode == NULL) {
        *headNode = newNode;
        return;
    }

    TodoNode *currentNode = *headNode;

    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

void removeNode(TodoNode **headNode, int id) {
    TodoNode *curr = *headNode;
    TodoNode *prev = NULL;

    if (curr == NULL || id <= 0)
        return;

    if (id == 1) {
        *headNode = curr->next;
        free(curr);
        return;
    }

    int counter = id - 1;

    while (counter > 0) {
        if (curr->next == NULL)
            return;

        counter -= 1;
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);
}

void editNode(TodoNode** headNode, const char* newDescription, const char* newDeadline, Status newStatus, int id) {
    TodoNode* curr = *headNode;
    int counter = id - 1;

    while (curr != NULL && counter > 0) {
        counter -= 1;
        curr = curr->next;
    }

    if (curr == NULL) return;

    if (newDescription != NULL) {
        strcpy(curr->description, newDescription);
    }

    if (newDeadline != NULL) {
        strcpy(curr->deadline, newDeadline);
    }

    if (newStatus != IGNORE_STATUS) {
        curr->status = newStatus;
    }
}
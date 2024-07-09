#include "logichandler.h"

void addTask(TodoNode** headNode, const char* description, const char* deadline) {
    appendNode(headNode, description, deadline, PENDING);
}

void removeTask(TodoNode** headNode, int id) {
    removeNode(headNode, id);
}

void markTaskAsComplete(TodoNode** headNode, int id) {
    editNode(headNode, NULL, NULL, COMPLETED, id);
}

void editTask(TodoNode** headNode, const char* description, const char* deadline, int id) {
    editNode(headNode, description, deadline, IGNORE_STATUS, id);
}

void listTask(TodoNode** headNode) {
    int counter = 1;
    TodoNode* currNode = *headNode;

    if (currNode == NULL) {
        puts("--- NO TASK ---");
        return;
    }

    while (currNode != NULL) {
        printf("%d. [%c] %s | Deadline: %s\n", counter, 
            currNode->status == COMPLETED ? 'X' : ' ',
            currNode->description,
            strlen(currNode->deadline) == 0 ? "NIL": currNode->deadline);
        
        counter += 1;
        currNode = currNode->next;
    }
}
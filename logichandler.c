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
    editNode(headNode, NULL, NULL, IGNORE_STATUS, id);
}

void decideTask(int choice) {
    switch(choice) {
        case '1':
        case '2':
    }
}
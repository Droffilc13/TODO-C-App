#ifndef LOGICHANDLER_H
#define LOGICHANDLER_H
#include "node.c"

void addTask(TodoNode** headNode, const char* description, const char* deadline);

void removeTask(TodoNode** headNode, int id);

void markTaskAsComplete(TodoNode** headNode, int id);

void editTask(TodoNode** headNode, const char* description, const char* deadline, int id);

void decideTask(int choice);

#endif

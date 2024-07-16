#include "uihandler.h"
#include "logichandler.h"
#include <stdlib.h>


#define TASK_MAX_SIZE 200

int main(void) {
    // Initialisation
    int isRunning = 1;
    TodoNode *taskList = NULL;
    int taskCount = 0;

    while (isRunning) {
        int choice = displayStartScreen();
        
        if (choice < 0) {
            printf("Unrecognised choice: Please input an integer value between 0 and 5: Error Code: %d\n", choice);
            continue;
        }

        switch (choice) {
            case 0:
                isRunning = 0;
                while (taskList != NULL) {
                    TodoNode* temp = taskList;
                    taskList = taskList->next;
                    free(temp);
                }
                break;
            case 1:
                puts("Adding Task");
                clear_input_buffer();
                if (taskCount > TASK_MAX_SIZE) {
                    puts("TODO list is full. Unable to add more task. Please top up for the premium $9.99 for more capacity!");
                } else {
                    char description[MAX_DESCRIPTION_SIZE];
                    char deadline[MAX_DEADLINE_SIZE];
                    
                    do {
                        printf("Enter Task Description (max %d characters): ", MAX_DESCRIPTION_SIZE);
                        fgets(description, sizeof(description), stdin);
                        description[strcspn(description, "\n")] = '\0';
                        clear_input_buffer();

                        if (strlen(description) == 0) {
                            puts("Description cannot be empty. Please try again");
                        } else if (strlen(description) >= MAX_DESCRIPTION_SIZE) {
                            puts("Description exceeds maximum length. Please try again.\n");
                        } else {
                            break;
                        }
                    } while(1);

                    do {
                        printf("Enter Deadline (dd/mm/yyyy max %d characters, optional): ", MAX_DEADLINE_SIZE - 1);
                        fgets(deadline, sizeof(deadline), stdin);
                        deadline[strcspn(deadline, "\n")] = '\0';
                        clear_input_buffer();

                        if (strlen(deadline) == 0) {
                            // Absence of deadline => represented as empty string
                            deadline[0] = '\0';
                            break;
                        } else if (strlen(deadline) != 10 || sscanf(deadline, "%2d/%2d/%4d", &(int){0}, &(int){0}, &(int){0}) != 3) {
                            printf("Invalid deadline format. Please enter in dd/mm/yyyy format.\n");
                        } else {
                            break;
                        }
                    } while(1);

                    addTask(&taskList, description, deadline);
                    taskCount += 1;

                    puts("Task added successfully");
                }
                break;
            case 2:
                puts("Delete Task");
                char idToRemove[4];
                int id2;

                clear_input_buffer();

                do {
                    printf("Enter a task ID to remove: ");
                    if (fgets(idToRemove, sizeof(idToRemove), stdin) != NULL) {
                        size_t length = strlen(idToRemove);
                        if (length > 0 && idToRemove[length - 1] == '\n') {
                            idToRemove[length - 1] = '\0';
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            clear_input_buffer();
                            continue;
                        }

                        if (isValidInteger(idToRemove)) {
                            id2 = atoi(idToRemove);
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        }

                        if (id2 <= 0 || id2 > taskCount) {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        } else {
                            break;
                        }

                    } else {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        continue;
                    }
                } while(1);

                removeTask(&taskList, id2);
                taskCount -= 1;
                puts("Task successfully removed");

                break;
            case 3:
                puts("Edit task");

                char description[MAX_DESCRIPTION_SIZE];
                char deadline[MAX_DEADLINE_SIZE];

                char idToEdit[4];
                int id3;

                do {
                    clear_input_buffer();
                    printf("Enter a task ID to edit: ");
                    if (fgets(idToEdit, sizeof(idToEdit), stdin) != NULL) {
                        size_t length = strlen(idToEdit);
                        if (length > 0 && idToEdit[length - 1] == '\n') {
                            idToEdit[length - 1] = '\0';
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        }

                        if (isValidInteger(idToEdit)) {
                            id3 = atoi(idToEdit);
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        }

                        if (id3 <= 0 || id3 > taskCount) {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        } else {
                            break;
                        }

                    } else {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        continue;
                    }
                } while(1);

                do {
                    clear_input_buffer(); // TODO: there seems to be an additonal \n at the start so need to remove..
                    printf("Enter Task Description (max %d characters): ", MAX_DESCRIPTION_SIZE - 1);
                    fgets(description, sizeof(description), stdin);
                    description[strcspn(description, "\n")] = '\0';
                    clear_input_buffer();

                    if (strlen(description) == 0) {
                        puts("Description cannot be empty. Please try again");
                    } else if (strlen(description) >= MAX_DESCRIPTION_SIZE) {
                        puts("Description exceeds maximum length. Please try again.\n");
                    } else {
                        break;
                    }
                } while(1);

                do {
                    printf("Enter Deadline (dd/mm/yyyy max %d characters, optional): ", MAX_DEADLINE_SIZE - 1);
                    fgets(deadline, sizeof(deadline), stdin);
                    deadline[strcspn(deadline, "\n")] = '\0';
                    clear_input_buffer();

                    if (strlen(deadline) == 0) {
                        // Absence of deadline => represented as empty string
                        deadline[0] = '\0';
                        break;
                    } else if (strlen(deadline) != 10 || sscanf(deadline, "%2d/%2d/%4d", &(int){0}, &(int){0}, &(int){0}) != 3) {
                        printf("Invalid deadline format. Please enter in dd/mm/yyyy format.\n");
                    } else {
                        break;
                    }
                } while(1);

                editTask(&taskList, description, deadline, id3);
                puts("Task edited successfully");
                break;
            case 4:
                puts("Listing Tasks...");
                listTask(&taskList);
                break;
            case 5:
                puts("Mark Task as Complete");
                char idToToggle[4];
                int id;
                clear_input_buffer();

                do {
                    printf("Enter a task ID to mark as complete: ");
                    if (fgets(idToToggle, sizeof(idToToggle), stdin) != NULL) {
                        size_t length = strlen(idToToggle);
                        if (length > 0 && idToToggle[length - 1] == '\n') {
                            idToToggle[length - 1] = '\0';
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            clear_input_buffer();
                            continue;
                        }

                        if (isValidInteger(idToToggle)) {
                            id = atoi(idToToggle);
                        } else {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        }

                        if (id <= 0 || id > taskCount) {
                            puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                            continue;
                        } else {
                            break;
                        }

                    } else {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        continue;
                    }
                } while(1);

                markTaskAsComplete(&taskList, id);
                puts("Task successfully marked as complete");
            default:
                printf("Unrecognised choice: Please input an integer value between 0 and 5: Error Code: %d\n", choice);
                break;
        }
        puts("");
    }


    return 0;
}

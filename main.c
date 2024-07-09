#include "uihandler.h"
#include "logichandler.h"

#define TASK_MAX_SIZE 200

int main(void) {
    // Initialisation
    int isRunning = 1;
    TodoNode *taskList = NULL;
    int taskCount = 0;

    while (isRunning) {
        int choice = displayStartScreen();
        
        if (choice < 0) {
            continue;
        }

        switch (choice) {
            case 0:
                isRunning = 0;
                break;
            case 1:
                puts("Adding Task");
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
                int idToRemove;

                do {
                    printf("Enter a task ID to edit: ");
                    if (scanf("%d", &idToRemove) != 1 || idToRemove < 1 || idToRemove > taskCount) {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        clear_input_buffer();
                    } else {
                        break;
                    }
                } while(1);

                removeTask(&taskList, idToRemove);
                taskCount -= 1;
                puts("Task successfully removed");

                break;
            case 3:
                puts("Edit task");

                int idToEdit;
                char description[MAX_DESCRIPTION_SIZE];
                char deadline[MAX_DEADLINE_SIZE];
                
                do {
                    printf("Enter a task ID to edit: ");
                    if (scanf("%d", &idToEdit) != 1 || idToEdit < 1 || idToEdit > taskCount) {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        clear_input_buffer();
                    } else {
                        break;
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

                editTask(&taskList, description, deadline, idToEdit);
                puts("Task edited successfully");
                break;
            case 4:
                puts("Listing Tasks...");
                listTask(&taskList);
                break;
            case 5:
                puts("Mark Task as Complete");
                int idToToggle;

                do {
                    printf("Enter a task ID to edit: ");
                    if (scanf("%d", &idToToggle) != 1 || idToToggle < 1 || idToToggle > taskCount) {
                        puts("Invalid id: Please enter a number corresponding to the id of an existing task");
                        clear_input_buffer();
                    } else {
                        break;
                    }
                } while(1);

                markTaskAsComplete(&taskList, idToToggle);
                puts("Task successfully marked as complete");
            default:
                printf("Unrecognised choice: Please input an integer value between 0 and 5: Error Code: %d\n", choice);
                break;
        }
        puts("");
    }


    return 0;
}

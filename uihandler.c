#include "uihandler.h"
#define CHOICE_SIZE 3

int displayStartScreen() {
    puts("#######################################");
    puts("#       Welcome to TODO assistant!    #");
    puts("#######################################");
   
    puts("Choose one of the following to get started\n");
    puts("(1) Add a Task");
    puts("(2) Delete a Task");
    puts("(3) Edit a Task");
    puts("(4) List Tasks");
    puts("(5) Mark Task as Done");
    puts("(0) Exit\n");

    printf("Enter your choice (integer from 0 to 5): ");
    char choice[CHOICE_SIZE];
    
    if (fgets(choice, sizeof(choice), stdin) == NULL) {
        return -1;
    }

    clear_input_buffer();
    
    if (strlen(choice) != 2 || choice[1] != '\n') {    
        return -2;
    }

    char extractedCharacter = choice[0];

    if (!isdigit(extractedCharacter)) {
        return -3;
    }

    int choiceNum = extractedCharacter - '0';

    if (choiceNum > 5) {
        return -4;
    }

    return choiceNum;
}
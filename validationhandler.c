#include "validationhandler.h"

void clear_input_buffer() {
    // Type of ch must be int to hold EOF value
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int isValidInteger(const char *str) {
    if (*str == '\0') {
        return 0;
    }
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

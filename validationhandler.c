#include "validationhandler.h"

void clear_input_buffer() {
    // Type of ch must be int to hold EOF value
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

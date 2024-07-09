#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to trim leading and trailing whitespace
char* trim(char* str) {
    char* end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    // If all spaces or empty string
    if(*str == 0) 
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

int main() {
    char str1[] = "   Hello, World!   ";
    char str2[] = "NoLeadingOrTrailingSpaces";
    char str3[] = "   LeadingSpaces";
    char str4[] = "TrailingSpaces   ";
    char str5[] = "       ";

    printf("'%s'\n", trim(str1));
    printf("'%s'\n", trim(str2));
    printf("'%s'\n", trim(str3));
    printf("'%s'\n", trim(str4));
    printf("'%s'\n", trim(str5));

    return 0;
}

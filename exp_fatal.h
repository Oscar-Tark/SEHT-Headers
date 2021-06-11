#include <unistd.h>
#include <stdio.h>
#include <string.h>

void exp_error(char* message)
{
        char buffer[2048];
        strcpy(buffer, "ERROR: ");
        strcat(buffer, message);
        perror(buffer);
        exit(1);
}

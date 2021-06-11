#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define EXP_EXIT_SUCCESS	0x00	//Program exited successfully
#define EXP_EXIT_ERROR		0x01	//Generic error thrown
#define EXP_EXIT_NUMARGS	0x02	//Not enough arguments supplied to the program
#define EXP_EXIT_SCRIPT		0x03	//Output script written for scorpion to use

#define EXP_EXIT_NETWORK_ERROR	0x04	//Exit on network error
#define EXP_EXIT_NETWORK_WRITE_ERROR	0x05

void exp_error(char* message, int exit_code)
{
        char buffer[2048];
        strcpy(buffer, "ERROR: ");
        strcat(buffer, message);
        perror(buffer);
        exit(exit_code);
}

void exp_error_socket(char* message, int socket_descriptor, int exit_code)
{
	close(socket_descriptor);
	exp_error(message, exit_code);
}

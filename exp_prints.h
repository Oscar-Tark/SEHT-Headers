#include <stdio.h>
#include <string.h>
#include "exp_types.h"

void exp_printf(const char* message)
{
	printf("%s\n", message);
	return;
}

void exp_printf_multiple(char* message[], int newline)
{
	//newline = boolean 0 or 1
	int size = sizeof(*message)/sizeof(message[0]);

	char format[4] = "%s";
	if(newline)
		strncat(format, "\n", 2);

	for(int i = 0; i <= size; i++)
		printf(format, message[i]);
	return;
}

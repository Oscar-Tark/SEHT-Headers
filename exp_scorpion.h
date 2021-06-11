#define SC_EXIT_SUCCESS	0xa0
#define SC_EXIT_ERROR	0xa1

//Defines weather the current instance is a scorpion instance
void exp_error_scorpion(char* message, int socketfd, int scorpion_exit_code)
{
	if(socketfd != -1)
		exp_error(message, scorpion_exit_code);
	exp_error(message, scorpion_exit_code);
}

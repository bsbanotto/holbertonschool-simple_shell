#include "shell.h"


/**
 * run - runs first arg
 * @args: first arg passed from shell loop
 * @program: Name of program
 * @n: int = 1
 *
 * Return: int, 1 to continue loop, any other int on failure
 */

int run(char *args, char *program, __attribute__((unused))int n)
{
	pid_t child;
	int status;

	n = 1;

	child = fork();
	if (child == -1)
	{
		perror("Error: fork failed");
		exit(99);
	}
	if (child == 0)
	{
		execvp(args, &program);
		exit(0);
	}
	else
	{
		do {
			waitpid(child, &status, WUNTRACED);
		} while (WIFEXITED(status) == 0 && WIFSIGNALED(status) == 0);
	}
	return (1);
}

#include "shell.h"


/**
 * run - runs first arg
 * @args: first arg passed from shell loop
 * @program: Name of program
 * @n: int = 1
 *
 * Return: int, 1 to continue loop, any other int on failure
 */

int run(char *path, char *argVec)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("Error: fork failed");
		exit(99);
	}
	if (child == 0)
	{
		execve(path, &argVec, NULL);
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

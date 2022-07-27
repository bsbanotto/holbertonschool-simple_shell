#include "shell.h"


/**
 * run - runs first arg
 * @args: first arg passed from shell loop
 * @program: Name of program
 * @n: int = 1
 *
 * Return: int, 1 to continue loop, any other int on failure
 */

int run(char **args, __attribute__((unused))char *program)
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
		check_valid_command(args);
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

/**
 * check_valid_command - Searches PATH for applicable command
 * @args: args passed from command line
 *
 * Return: 0 on success
 */

int check_valid_command(char **args)
{
	char *result;
	path_t *main_path = path_list();

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (execve(args[0], args, environ) == -1)
		exit(99);
	}
	else
	{
		result = (check_path(main_path, args[0]));
		if (!result)
			exit(99);
		if (execve(result, args, environ) == -1)
			exit(99);
	}

	return (0);
}

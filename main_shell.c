#include "shell.h"

/**
 * main - Simple Shell Project
 * @argc: count of args
 * @argv: vector of pointers to args
 *
 * Return: 0 on success
 */

int main(int argc, char *argv[])
{
	if (argc == 0)
		return (0);
	cmd_prompt(argv[0]);
	return (0);
}

/**
 * prompt_line - Prints command line prompt
 *
 * Return: void
*/

void prompt_line(void)
{
	write(1, "$ ", 2);
}

/**
 * clear - Clears the terminal text
 *
 * Return: zero on success;
 */

char clear(void)
{
	write(1, "\033[H033[J", 6);
	return (0);
}

/**
 * cmd_prompt - Takes input from main and executes infinite loop
 * @program: passed in argument for what to do
 *
 * Return: void
 */

void cmd_prompt(__attribute__((unused))char *program)
{
	char *buffer = NULL;
	size_t bufsize;
	char *tokens;
	char *duplicate;
	char *first_arg;
	int i = 0, status = 1;
	char *path;

	path = malloc(PATH_MAX * sizeof(char));
	path = getcwd(path, sizeof(PATH_MAX));

	printf("%s", path);

	while (status)
	{
		printf("$ ");
		getline(&buffer, &bufsize, stdin);
		duplicate = _strdup(buffer);
		tokens = strtok(duplicate, " \n\t\a");

		while (i < 1)
		{
			first_arg = tokens;
			printf("%s\n", first_arg);
			tokens = strtok(NULL, " \n\t\a");
			i++;
		}
		status = run(path, tokens);

		printf("%s", buffer);
		i--;
	}
}

/**
 * read_input - Takes arguments, tokenizes
 *
 * Return: Pointer to string
 */

char *read_input(void)
{
	char *buffer = NULL;
	size_t buffersize = 0;

	if (isatty(STDIN_FILENO) == 1)
		prompt_line();
	if (getline(&buffer, &buffersize, stdin) <= 0)
	{
		if (isatty(STDIN_FILENO) == 1)
			write((STDOUT_FILENO), "\n", 1);
		exit(0);
	}
	return (buffer);
}

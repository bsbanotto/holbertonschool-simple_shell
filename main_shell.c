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
	char *dup;
	int i = 0, status = 1;
	char *path = "/usr/bin/";
	char pathdup[] = "/usr/bin/";

	while (status)
	{
		printf("$ ");
		getline(&buffer, &bufsize, stdin);
		dup = _strdup(buffer);
		tokens = strtok(dup, " \n\t\a");

		while (i < 1)
		{
			char const *first_arg = tokens;
			printf("%s\n", first_arg);
			tokens = strtok(NULL, " \n\t\a");
			i++;
		}

		path = malloc(sizeof(char) * (strlen(dup) + strlen(path) + 1));
		path = strcat(pathdup, first_arg);
		path = strcat(pathdup, first_arg);
		
		if (path == NULL)
			printf("Nope. - - - - - - - - - - - -");
		else
			printf("Path is: %s\n\n\n", path);

		execve(path, first_arg, NULL);

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

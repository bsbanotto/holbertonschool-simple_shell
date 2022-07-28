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
 * cmd_prompt - Takes input from main and executes infinite loop
 * @program: passed in argument for what to do
 *
 * Return: void
 */

void cmd_prompt(char *program)
{
	char *line;
	char **args;
	int i = 0, status = 1;
	path_t *env_path = _environment();
	path_t *main_path = path_list();

	signal(SIGINT, signal_handler);

	while (status)
	{
		line = read_cmd();
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		args = tokens(line, " \t\a\n");
		if (check_if_builtin(args, line) == 1)
			status = run(args, program);
		while (args[i] != NULL)
		{
		if (args[i])
			free(args[i]);
		i++;
		}

	if (line)
		free(line);
	if (args)
		free(args);
	}
	free(args);
	free(line);
	free_linked_list(main_path);
	free_linked_list(env_path);
}

/**
 * read_cmd - Takes arguments, tokenizes
 *
 * Return: Pointer to string
 */

char *read_cmd(void)
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

/**
 * signal_handler - Handles terminate signal
 * @sig: signal
 */

void signal_handler (int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		prompt_line();
	}
}

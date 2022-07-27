#include "shell.h"

/**
 * check_if_builtin - checks if a builtin command has been called
 * @args: array of pointers to arguments
 * @cmd_line: user input from command line
 *
 * Return: 0 on proper call, 1 on failure
 */

int check_if_builtin(char **args, char *cmd_line)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		shell_exit(args, cmd_line);
		return (0);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		return (0);
	}
	else
		return (1);
}

/**
 * shell_exit - exits process
 * @args: arguments
 * @cmd: user input
 */

void shell_exit(char **args, char *cmd)
{
	unsigned int i = 0;
	path_t *env_path = _environment();
	path_t *main_path = path_list();

	if (!cmd)
		free(cmd);
	if (!args)
		free(args);
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	free(cmd);
	free_linked_list(main_path);
	free_linked_list(env_path);

	exit(0);
}

/**
 * print_env - prints env var array
 */

void print_env(void)
{
	path_t *temp;
	path_t *env_path = _environment();

	temp = env_path;
	while (temp)
	{
		write(1, temp->dir, _strlen(temp->dir));
		write(1, "\n", 1);
		temp = temp->next;
	}
}

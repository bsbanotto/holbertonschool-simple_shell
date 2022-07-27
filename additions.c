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


/**
 * free_linked_list - Frees a linked list
 * @head: pointer to head of linked list
 *
 * Return: void
 */

void free_linked_list(path_t *head)
{
	if (head == NULL)
		return;
	if (head->next != NULL)
		free_linked_list(head->next);
	free(head->dir);
	free(head);
}


/**
 * make_path_list - Makes path linked list
 *
 * Return: Pointer to head of linked list
 */

path_t *make_path_list(void)
{
	path_t *head, *temp;
	char *path_name = NULL, *tok;

	temp = malloc(sizeof(path_t));
	if (!temp)
		exit(-1);

	path_name = _getenv("PATH");

	if (!path_name)
	{
		free(temp);
		return (NULL);
	}
	tok = strtok(path_name, ":");

	head = temp;
	while (tok)
	{
		temp->dir = _strdup(tok);
		tok = strtok(NULL, ":");
		if (tok)
		{
			temp->next = malloc(sizeof(path_t));
			if (!temp->next)
			{
				free_linked_list(head);
				exit(-1);
			}
			temp = temp->next;
		}
		else
			temp->next = NULL;
	}
	free(path_name);
	return (head);
}

/**
 * cmd_count - Counts number of commands entered
 * @s: pointer to command line string
 *
 * Return: count of commands
 */

int cmd_count(char *s)
{
	int i;
	int words = 1, delims = 1;

	if (!s)
		return (-1);

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ')
		{
			if (delims == 0)
			{
				words++;
				delims = 1;
			}
		}
		else
			delims = 0;
	}
	return (words);
}

/**
 * tokens - tokenizes command line string
 * @buffer: command line string to tokenize
 * @delim: delimeter
 *
 * Return: double pointer to tokens
 */

char **tokens(char *buffer, char *delim)
{
	char *token, *buffercopy;
	int i = 0;
	int command_count = cmd_count(buffer);
	char **commands = malloc(sizeof(char *) * (command_count + 1));

	if (!commands)
	{
		perror("Error\n");
		exit(-1);
	}
	buffercopy = _strdup(buffer);
	if (!buffercopy)
	{
		perror("_strdup error\n");
		return (NULL);
	}
	token = strtok(buffercopy, delim);

	while (token)
	{
		commands[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (!commands[i])
		{
			perror("malloc error");
			while (i >= 0)
			{
				free(commands[i]);
				i--;
			}
			free(commands);
			exit(-1);
		}
		_strcpy(commands[i], token);
		i++;
		token = strtok(NULL, delim);
	}
	commands[i] = NULL;
	free(buffercopy);
	return (commands);
}

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
	else if (_strcmp[0], "env") == 0)
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
	path_t *env_path = _enviornment();
	path_t *main_path = make_path_list();

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
	path_t *env_path = _enviornment();

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
 * path_concat - concats path with command
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to concat path string
 */

char *path_concat(char *s1, char *s2)
{
	int i, j;
	char *path_str;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	path_str = malloc(sizeof(char) * (_strlen(s1) + _strlen(s2) + 2));
	if (path_str == NULL)
		exit(-1);

	for (i = 0; s1[i]; i++)
		path_str[i] = s1[i];
	path_str[i] = '/';
	i++;
	for (j = 0; s2[j]; j++)
		path_str[i + j] = s2[j];
	path_str[i + j] = '\0';
	return (path_str);
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
 * _getenv - searches environment list for variable name
 * @name: name of the variable
 *
 * Return: returns a pointer to the corresponding value;
 */
char *_getenv(char *name)
{
	unsigned int y;
	char *match, *copy;
	path_t *temp;
	path_t *env_path = _environment();

	match = NULL;
	temp = env_path;

	while (temp)
	{
		y = 0;
		while (name[y])
		{
			if (name[y] != temp->dir[y])
				break;
			if (name[y + 1] == '\0' && temp->dir[y + 1] == '=')
				match = temp->dir;
			y++;
		}
		if (match)
			break;
		temp = temp->next;
	}

	copy = malloc(sizeof(char *) * (_strlen(match)));
	if (!copy)
		exit(-1);
	_strcpy(copy, match);

	return (copy);
}

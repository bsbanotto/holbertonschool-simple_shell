#include "shell.h"

/**
 * _environment - Makes a linked list of environment variables
 *
 * Return: pointer to the head of the list
 */

path_t *_environment(void)
{
	path_t *head;
	path_t *temp;
	int i = 0;

	head = malloc(sizeof(path_t));
	if (!head)
		exit(-1);
	temp = head;
	while (environ[i])
	{
		temp->dir = _strdup(environ[i]);
		if (environ[i + 1] != NULL)
		{
			temp->next = malloc(sizeof(path_t));
			if (!temp->next)
				exit(-1);
			temp = temp->next;
		}
		i++;
	}
	temp->next = NULL;
	return (head);
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
/**
 * check_path - checks path
 * @head: head of PATH linked list
 * @command: command from arguments
 *
 * Return: returns the proper path or NULL on failure
 */

char *check_path(path_t *head, char *command)
{
	path_t *temp;
	char *filename;
	struct stat st;

	if (!command || !head)
		return (NULL);

	temp = head;
	while (temp)
	{
		filename = path_concat(temp->dir, command);
		if (!filename)
			return (NULL);
		if (stat(filename, &st) == 0)
		{
			return (filename);
		}
		free(filename);
		temp = temp->next;
	}
	return (NULL);
}

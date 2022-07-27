#include "shell.h"

/**
 * free_linked_list - frees a linked list from passed in head pointer
 *
 * @head: pointer to head of list to be freed
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

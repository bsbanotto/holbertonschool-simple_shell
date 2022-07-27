#include "shell.h"

/**
 * print_list - prints all elements of path_t list
 *
 * @h: pointer to head
 *
 * Return: number of nodes
 */

int print_list(const path_t *h)
{
	int nodes = 0;

	while (h)
	{
		if (h->dir == NULL)
			printf("(nil)");

		else
			printf("%s/", h->dir);
		nodes++;
		h = h->next;
	}

	return (nodes);
}



/**
 * add_node_end - adds a new node at the end of a linked list
 *
 * @head: pointer to head
 * @dir: directory in path
 *
 * Return: pointer to head
 */

path_t *add_node_end(path_t **head, char *dir)
{
	path_t *new_list, *temp;

	if (dir != NULL)
	{
		new_list = malloc(sizeof(path_t));
		if (new_list == NULL)
			return (NULL);

		new_list->dir = strdup(dir);
		new_list->next = NULL;

		if (*head == NULL)
		{
			*head  = new_list;
			return (*head);
		}
		else
		{
			temp = *head;
			while (temp->next)
				temp = temp->next;

			temp->next = new_list;
			return (temp);
		}
	}

	return (NULL);
}


/**
 * arg_count - gets num of args from path
 *
 * @path: path variable to be modified
 *
 * Return: num of args
 */

int arg_count(char *path)
{
	int count = 1;
	char *dup = strdup(path);
	char *tokens = strtok(dup, " \n\t\a");

	while (tokens != NULL)
	{
		count++;
		tokens = strtok(NULL, " ");
	}
	return (count);
}

/**
 * path_list - turns tokenized path into linked list
 *
 * Return: pointer to head
 */

path_t *path_list(void)
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

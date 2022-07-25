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
 * path_list - turns tokenized path into linked list
 *
 * @path: path variable to be modified
 *
 * Return: pointer to head
 */

int arg_count(char *path)
{
	int count = 1;
	char* dup = strdup(path);
	char *tokens = strtok(dup, " \n\t\a");

	while (tokens != NULL)
	{
		count++;
		tokens = strtok(NULL, " ");
	}
	return(count);
}


path_t path_list(char *path)
{
        int i = 0;
	path_t *head;
	char *p = strtok(path, "/");
	path_t *first = malloc(sizeof(path_t));
	int count = arg_count(path);

	head = first;
	first->dir = p;
	first->next = NULL;

	if (first == NULL)
	{
		head = first;
		return (*head);
	}

	/* Saves tokens to linked list */
	while(i < count)
	{
		p = strtok(NULL, " ");
		add_node_end(&head, p);
	}

	return(*head);
}

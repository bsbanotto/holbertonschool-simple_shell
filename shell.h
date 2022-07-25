#ifndef SHELL_H
#define SHELL_H

/* Libraries */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

/* Path linked list structure */

/**
 * struct path_s - path singly linked list
 * @dir: directories in path
 * @next: points to next node
 *
 * Description: singly linked list ndoe structure for path
 */

typedef struct path_s
{
	char *dir;
	struct path_s *next;
} path_t;

extern char **environ;

/* Linked List Prototypes */

int print_list(const path_t *h);
path_t *add_node_end(path_t **head, char *dir);
path_t path_list(char *path);

/* String Prototypes */

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *src);
int _strcmp(char *s1, char *s2);
char *path_concat(char *s1, char *s2);

/* Shell Prototypes */

void cmd_prompt(char *program);
void prompt_line(void);
char clear(void);
char *read_input(void);
int run(char *args, char *program, int n);
int check_command(char *args, char *program, int n);



#endif

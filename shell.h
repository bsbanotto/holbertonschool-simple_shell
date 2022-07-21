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

/* String Prototypes */

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *src);
char _strcmp(char *s1, char *s2);
char *path_concat(char *s1, char *s2);

/* Shell Prototypes */

void cmd_prompt(char *program);
void prompt_line(void);
char clear(void);
char *read_input(void);




#endif
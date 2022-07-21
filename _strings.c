#include "shell.h"

/**
 * _strlen - Returns the length of a string
 * @s: string to analyze
 *
 * Return: Length of string
 */

int _strlen(char *s)
{
	int len = 0;

	while (*s)
	{
		s++;
		len++;
	}

	return (len);
}

/**
 * _strcpy - Copies a given string
 * @dest: destination string
 * @src: source string
 *
 * Return: Pointer to destination string
 */

char *_strcpy(char *dest, char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		src++;
		dest++;
	}

	*dest = '\0';

	return (start);
}

/**
 * *_strdup - Duplicates a given string
 * @src: Provided string
 *
 * Return: Pointer to duplicate string
 */

char *_strdup(char *src)
{
	int i;
	char *s;

	if (src == NULL)
		return (NULL);

	s = malloc(sizeof(char) * (_strlen(src) + 1));
	if (s == NULL)
		exit(-1);
	for (i = 0; src[i] != '\0'; i++)
	{
		s[i] = src[i];
	}
	s[i] = '\0';

	return (s);
}

/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: integer
 */

int _strcmp(char *s1, char *s2)
{
	int compare = 0;

	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	compare = *s1 - *s2;

	return (compare);
}

/**
 * path_concat - concatenates path with command
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to concatenated path string
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
	if (s == NULL)
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

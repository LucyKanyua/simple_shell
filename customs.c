#include "shell.h"

/**
 * _strcpy - copies the string
 * @src: the source of the string
 * @dest: the destination of the string
 * Return: the destination of the string
 */
char *_strcpy(char *dest, char *src)
{
	int i = -1;

	do {
		i++;
		dest[i] = src[i];
	} while (src[i] != '\0');
	return (dest);
}
/**
 * _strcat - concatenates a string
 * @dest: destination of the string
 * @src: source of the string
 * Return: the concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int index = 0;
	int dest_len = 0;

	while (dest[index++])
		dest_len++;
	for (index = 0; src[index]; index++)
		dest[dest_len++] = src[index];
	return (dest);
}
/**
 * _strcmp - compares a string
 * @s1: string one
 * @s2: string two
 * Return: integer
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 * _strdup - duplicates a string
 * @src: string to be duplicated
 * Return: duplicated string
 */
char *_strdup(char *src)
{
	size_t len = _strlen(src) + 1;
	char *dest = malloc(len);

	if (dest == NULL)
	{
		return (NULL);
	}
	_strcpy(dest, src);
	return (dest);
}
/**
 * _strlen - calculates the length of a string
 * @src: string
 * Return: length of the string
 */
size_t _strlen(char *src)
{
	int len = 0;

	while (*src != '\0')
	{
		len++;
		src++;
	}
	return (len);
}

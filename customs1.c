#include "shell.h"

/**
 * _strcspn - returns the length of the initial segment of a string
 * @s1: string 1
 * @s2: string 2
 * Return: the length of the initial segment
 */
size_t _strcspn(char *s1, char *s2)
{
	size_t i, j;

	for (i = 0; s1[i] != '\0'; i++)
	{
		for (j = 0; s2[j] != '\0'; j++)
		{
			if (s1[i] == s2[j])
			{
				return (i);
			}
		}
	}
	return (i);
}
/**
 * _strncmp - compares the first n characters of two strings
 * @s1: string 1
 * @s2: string 2
 * @n: maximum number of characters to compare
 * Return: integer
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t j;

	for (j = 0; j < n; j++)
	{
		if (s1[j] == '\0' || s1[j] != s2[j])
		{
			return (s1[j] - s2[j]);
		}
	}
	return (0);
}
/**
 * _strncpy - copies specified number of characters from one string to another
 * @dest: destination of the string
 * @src: source of the string
 * @n: number of characters
 * Return: the copied string
 */
char *_strncpy(char *dest, char *src, size_t n)
{
	size_t j;

	for (j = 0; j < n && src[j] != '\0'; j++)
	{
		dest[j] = src[j];
	}
	for (; j < n; j++)
	{
		dest[j] = '\0';
	}
	return (dest);
}
/**
 * _strchr - searches for the first occurrence of char
 * @str: string
 * @c: char to search
 * Return: pointer to location or NULL
 */
char *_strchr(char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
* free_token - frees array of tokens
* @tokens: array
* @count: number of items in array
* Return: void
*/
void free_token(char **tokens, int count)
{
	int k = 0;

	for (k = 0; k < count && tokens[k] != NULL; k++)
	{
		free(tokens[k]);
		tokens[k] = NULL;
	}
}

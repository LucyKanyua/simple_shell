#include "shell.h"


/**
* _myfree_list - frees array
* @commands: array to be freed
* Return: nothing
*/
void _myfree_list(char **commands)
{
	int i;

	for (i = 0; i < 10 && commands[i] != NULL; i++)
	{
		free(commands[i]);
		commands[i] = NULL;
	}
}

/**
* clean_list - frees array
* @list: array to be freed
* Return: nothing
*/

void clean_list(char **list)
{
	int i = 0;

	for (; i < 5000; i++)
	{
		if (list[i] != NULL)
			free(list[i]);
	}
}


/**
* print_error - prints error to stderr
* @valid: validation
* @program_name: program name
* @count: count
* @commands: commands passed
* Return: nothing
*/
int print_error(int valid, char **program_name, int *count, char *commands[])
{
	char *temp = _strdup(*program_name);
	char *str = malloc(100);
	char *num_str = itoa(*count, str);


	if (valid == 0)
	{
		write(STDERR_FILENO, temp, _strlen(temp));
		write(STDERR_FILENO, " : ", 3);
		write(STDERR_FILENO, num_str, _strlen(num_str));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, commands[0], _strlen(commands[0]));
		write(STDERR_FILENO, " :", 2);
		write(STDERR_FILENO, " not found\n", 11);

		if (temp != NULL)
			free(temp);
		if (str != NULL)
			free(str);
		return (-1);

	}
	if (temp != NULL)
		free(temp);
	if (str != NULL)
		free(str);
	return (0);
}

/**
* free_item - frees memory address of a string
* @str: string
* Return: nothing
*/
void free_item(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

/**
* free_dptr - frees double pointer
* @dptr: pointer to be freed
* Return: nothing
*/
void free_dptr(char **dptr)
{
	if (dptr != NULL)
	{
		free(dptr);
		dptr = NULL;
	}
}

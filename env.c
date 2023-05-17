#include "shell.h"

/**
* myenv - sets and unsets env
* @head: pointer to head of a linked list
* Return: nothing
*/
void myenv(Node **head)
{
	Node *list = *head;
	char *temp[10];
	int i = 0;
	
	/*iterates linked list adds commands in each node to temp[]*/
	while (list != NULL)
	{
		temp[i++] = strdup(list->cmd);
		list = list->next;
	}
	/*sets last item of temp[] to null*/
	temp[i] = NULL;
	
	/*checks if first item in temp[] is "setenv"*/
	if (strcmp(temp[0], "setenv") == 0)
	{
		/*checks if items in temp[] are not 3*/
		if (i != 3)
			write(STDERR_FILENO, "./hsh : setenv : invalid number of arguments", 44);
		/*if items are 3 _setenv() is called to set environment*/
		else
		{
			if (setenv(temp[1], temp[2], 1) != 0)
				write(STDERR_FILENO, "./hsh : setenv : failed", 22);
				
		}

	} 
	/*checks if first item in temp[] is "unsetenv"*/
	else if (strcmp(temp[0], "unsetenv") == 0)
	{
		/*checks if items in temp[] are not 2*/
		if (i != 2)
			write(STDERR_FILENO, "./hsh : unsetenv : invalid number of arguments", 46);
		/*if items are 2 _unsetenv() is called to unset environment*/
		else
			if (unsetenv(temp[1]) != 0)
				write(STDERR_FILENO, "./hsh : usetenv : failed", 24);
	}
	/*free temp[]*/
	i = 0;
	while (temp[i] != NULL)
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
}


/**
 * _unsetenv - unsets environment
 * @name: name
 * Return: 0 on success
 */

int _unsetenv(char *name) /*has bugs*/
{
	char **envp = environ;
	int name_len = strlen(name);
	char *env_var;

	while (*envp != NULL)
	{
		env_var = *envp;

		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
		{
			char **next_env = envp + 1;

			while (*next_env != NULL)
			{
				*envp = *next_env;
				envp++;
				next_env++;
			}

			*envp = NULL;
			return (0);
		}
		 envp++;
	}
	return (0);
}
/**
* mycd - implements cd
* @head: ponter to head of a linked list
* Return: void
*/
void mycd(Node **head)
{
	/*creates reference to head of linked list*/
	Node *list = *head;
	char *temp[200];
	int i = 0, j = 0;
	size_t dir_len = 1024;
	char *current_wd = NULL, *current_dir = NULL;

	/*itarates linked list and adds each command to temp[] */
	while (list != NULL)
	{
		/*duplicates command in the current node to temp[] */
		temp[i++] = strdup(list->cmd);
		/*current node points to next */
		list = list->next;
	}
	
	/*calls _mycd() to execute commands in temp[]*/
	_mycd(temp, i, &current_wd, &current_dir, dir_len);
	
	/*frees current_wd if its not null*/
	if (current_wd != NULL)
	{
		free(current_wd);
		current_wd = NULL;
	}
	/*frees current_dir if its not null*/
	if (current_dir != NULL)
	{
		free(current_dir);
		current_dir = NULL;
	}
	/*frees each item in temp[] when the item is not null*/
	for (j = 0; j < i && temp[j] != NULL; j++)
	{
		free(temp[j]);
		temp[j] = NULL;
	}
}

/**
 * print_envp - prints environment content
 * Return: nothing
 */
void print_env(void)
{
	/*initializes a pointer to environ*/
	char **env = environ;

	/*iterates environ and prints each variable followed by a new line*/
	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}





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
	
	while (list != NULL)
	{
		temp[i++] = strdup(list->cmd);
		list = list->next;
	}
	if (strcmp(temp[0], "setenv") == 0)
	{
		if (i != 3)
			perror("./shell");
		else
			_setenv(temp[1], temp[2], 0);

	} else if (strcmp(temp[0], "unsetenv") == 0)
	{
		if (i != 2)
			perror("./shell");
		else
			_unsetenv(temp[1]);
	}
}


/**
 * _unsetenv - unsets environment
 * @name: name
 * Return: 0 on success
 */

int _unsetenv(char *name)
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
	Node *list = *head;
	char *temp[10];
	int i = 0, j = 0;
	size_t dir_len = 1024;
	char *current_wd = NULL, *current_dir = NULL;

	while (list != NULL)
	{
		temp[i++] = strdup(list->cmd);
		list = list->next;
	}
	_mycd(temp, i, &current_wd, &current_dir, dir_len);
	
	if (current_wd != NULL)
	{
		free(current_wd);
		current_wd = NULL;
	}
	if (current_dir != NULL)
	{
		free(current_dir);
		current_dir = NULL;
	}
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
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}





#include "shell.h"

/**
* _or - handles logical operator OR
* @head: pointer to head of a linked list
* @status: status
* @count: number of executions
* @_list: list of executables
* @program_name: program_name
* Return: void
*/
void _or(Node **head, int *status, int *count,
		char **program_name, char **_list)
{
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0;

	*status = -1;

	while (list != NULL)
	{
		if (_strcmp(list->cmd, "||") != 0)
		{
			temp[i++] = _strdup(list->cmd);
			temp[i] = NULL;
		}
		if (_strcmp(list->cmd, "||") == 0 || list->next == NULL)
		{
			if (*status != 0)
			{
				*status = myexecve(temp, count, program_name, _list);
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				i = 0;
			}
		}
		list = list->next;
	}
	for (j = 0; j < i; j++)
	{
		if (temp[j] != NULL)
		{
			free(temp[j]);
			temp[j] = NULL;
		}
	}

}


/**
* _and - handles logical operator AND
* @head: pointer to head of a linked list
* @status: status
* @count: number of executions
* @_list: list of executables
* @program_name: program_name
* Return: void
*/
void _and(Node **head, int *status, int *count,
		char **program_name, char **_list)
{
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0;

	*status = 0;
	while (list != NULL)
	{
		if (_strcmp(list->cmd, "&&") != 0)
		{
			temp[i++] = strdup(list->cmd);
			temp[i] = NULL;
		}
		if (_strcmp(list->cmd, "&&") == 0 || list->next == NULL)
		{
			if (*status == 0)
			{
				*status = myexecve(temp, count, program_name, _list);
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				i = 0;
			}
		}
		list = list->next;
	}
	for (j = 0; j < i; j++)
	{
		if (temp[j] != NULL)
		{
			free(temp[j]);
			temp[j] = NULL;
		}
	}
}



/**
* var_replace - handles variable replacement
* @head: pointer to head of linked list containing commands
* @status: exit status of previous child process
* Return: nothing
*/
void var_replace(Node **head, int *status, char *path)
{
	Node *list = (*head)->next;
	char *temp = NULL, *_path;

	print_pid(head);
	print_status(head, status);
	if (_strcmp(list->cmd, "$$") != 0 && _strcmp(list->cmd, "$?") != 0)
	{
		char *str = NULL;
		
		temp = _strdup(list->cmd);
		str = strndup(temp + 1, _strlen(temp) - 1);
		_path = _getenv(str);
		if (!_path)
			write(STDOUT_FILENO, "\n", 1);
		else if (_strcmp(str, "PATH") == 0)
		{
			write(STDOUT_FILENO, path, _strlen(path));
			write(STDOUT_FILENO, "\n", 1);
		} else
		{
			write(STDOUT_FILENO, _path, _strlen(_path));
			write(STDOUT_FILENO, "\n", 1);
		}
		free_item(str);
	}
	free_item(temp);
	
}

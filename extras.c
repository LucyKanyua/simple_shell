#include "shell.h"

/**
* myexecve - executes commands
* @commands: array of commands
* Return: nothing
*/
void myexecve(char *commands[], int status)
{
	char str[100];
	pid_t pid;
	int i = 0;
	
	if (commands[0][0] == '/')
	{
		strcpy(str, commands[0]);
	} else
	{
		strcpy(str, "/bin/");
		strcat(str, commands[0]);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error forking\n");
	} else if (pid == 0)
	{
		if (execve(str, commands, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	} else
	{
		waitpid(pid, &status, 0);
	}
	for (i = 0; i < 10 && commands[i] != NULL; i++)
	{
		free(commands[i]);
		commands[i] = NULL;
	}
}

/**
* _parser - parse commands
* @head: pointer to head of a linked list
* Return: nothing
*/
void _parser(Node **head)
{
	if (strcmp((*head)->cmd, "exit") == 0)
	{
		myexit(head);
	} else if (strcmp((*head)->cmd, "env") == 0)
	{
		print_env();
	} else if (strcmp((*head)->cmd, "cd") == 0)
	{
		mycd(head);
	} else
	{
		command_alloc(head);
	}
}


/**
* _mycd - extension of mycd that implements cd
* @temp: array of commands
* @i: index
* @current_wd: pointer to cwd
* @current_dir: pointer to current directory
* @dir_len: directory length
*/
void _mycd(char *temp[], int i, char **current_wd, char **current_dir, size_t dir_len)
{
	if (strcmp(temp[0], "cd") == 0)
	{
		if (i == 1)
		{
			chdir(_getenv("HOME"));
			*current_wd = getcwd(*current_dir, dir_len);
			_setenv("OLDPWD", *current_wd, 1);
			_setenv("PWD", *current_wd, 1);
		}
		else if (i == 2 && strcmp(temp[1], "-") == 0)
		{
			char *old_pwd = _getenv("OLDPWD");
			if (old_pwd != NULL)
			{

				chdir(old_pwd);
				*current_wd = getcwd(*current_dir, dir_len);
				_setenv("OLDPWD", _getenv("PWD"), 1);
				_setenv("PWD", *current_wd, 1);
			}
		}
		else if (i == 2)
		{
			chdir(temp[1]);
			*current_wd = getcwd(*current_dir, dir_len);
			_setenv("OLDPWD", _getenv("PWD"), 1);
			_setenv("PWD", *current_wd, 1);
		}
		else
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
}


/**
* free - frees a linked list
* @head: pointer to head of a linked list
* Return: void
*/
void free_head(Node **head)
{
	if (*head != NULL)
	{
		free_list(head);
		*head = NULL;
	}
}

/**
* _whitespace - handles whitespace command
* @buffer: buffer
* Return: void
*/
void _whitespace(char **buffer)
{
	if (strspn(*buffer, " \t\n\r") == strlen(*buffer))
	{
		free(*buffer);
		exit(0);
	}
}
	

#include "shell.h"

/**
* myexecve - executes commands
* @commands: array of commands
* @count: number of executions
* @list: list of executables
* @program_name: program_name
* Return: exit status of execve
*/
int myexecve(char *commands[], int *count, char **program_name, char **list)
{
	char str[100];
	int i = 0;
	int status = 0;
	pid_t pid;

	if (commands[0][0] == '/')
		_strcpy(str, commands[0]);
	else
	{
		_strcpy(str, "/bin/");
		_strcat(str, commands[0]);
	}
	if (check_command(commands, program_name, count, list) == -1)
	{
		_myfree_list(commands);
		status = 127;
	} else
	{
		pid = fork();
		if (pid == -1)
			write(STDOUT_FILENO, "fork\n", 5);
		else if (pid == 0)
		{

			if (execve(str, commands, environ) == -1)
			{
				perror(*program_name);
			}
		}
		else
			waitpid(pid, &status, 0);
		for (i = 0; i < 10 && commands[i] != NULL; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}
	}
	return (status);
}

/**
* _parser - parse commands
* @head: pointer to head of a linked list
* @count: number of executions
* @program_name: program_name
* @list: list of executables
* @status: return status of child process
* Return: nothing
*/
void _parser(Node **head, int *status,
		int *count, char **program_name, char **list)
{
	char *echo_cmd = NULL;

	if (*head != NULL)
	{
		if (_strcmp((*head)->cmd, "echo") == 0 && (*head)->next != NULL)
			echo_cmd = _strdup((*head)->next->cmd);
		if (_strcmp((*head)->cmd, "exit") == 0)
		{
			myexit(head, list);
		}
		else if (_strcmp((*head)->cmd, "env") == 0)
		{
			print_env();
		}
		else if (_strcmp((*head)->cmd, "cd") == 0)
		{
			mycd(head);
		}
		else if (_strcmp((*head)->cmd, "setenv") == 0
				|| _strcmp((*head)->cmd, "unsetenv") == 0)
		{

			myenv(head);
		}
		else if (_strcmp((*head)->cmd, "echo") == 0
				&& echo_cmd != NULL && echo_cmd[0] == '$')
		{
			var_replace(head, status);
		}

		else
			command_alloc(head, status, count, program_name, list);

		if (echo_cmd != NULL)
		{
			free(echo_cmd);
			echo_cmd = NULL;
		}
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
void _mycd(char *temp[], int i, char **current_wd,
		char **current_dir, size_t dir_len)
{
	if (_strcmp(temp[0], "cd") == 0)
	{
		if (i == 1)
		{
			chdir(_getenv("HOME"));
			*current_wd = getcwd(*current_dir, dir_len);
			setenv("OLDPWD", *current_wd, 1);
			setenv("PWD", *current_wd, 1);
		}
		else if (i == 2 && _strcmp(temp[1], "-") == 0)
		{
			char *oldpwd = _getenv("OLDPWD");
			size_t len = _strlen(oldpwd);

			write(STDOUT_FILENO, oldpwd, len + 1);
			write(STDOUT_FILENO, "\n", 1);
			chdir(_getenv("OLDPWD"));
			*current_wd = getcwd(*current_dir, dir_len);
			setenv("OLDPWD", _getenv("PWD"), 1);
			setenv("PWD", *current_wd, 1);
		}
		else if (i == 2)
		{
			chdir(temp[1]);
			*current_wd = getcwd(*current_dir, dir_len);
			setenv("OLDPWD", _getenv("PWD"), 1);
			setenv("PWD", *current_wd, 1);
		}
		else
		{
			write(STDERR_FILENO, "cd", 2);
		}
	}
}


/**
* free_head - frees a linked list
* @head: pointer to head of a linked list
* Return: void
*/
void free_head(Node **head)
{
	/*checks if linked list is not null and calls free_list() to free it*/
	if (*head != NULL)
	{
		/*frees linked list*/
		free_list(head);
		/*s=assigns null to avoid double free*/
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
	/*checks if whitespace is entered and frees buffer then exits with status 0*/
	if (_strcspn(*buffer, " \t\n\r") == _strlen(*buffer))
	{
		free(*buffer);
		exit(0);
	}
}


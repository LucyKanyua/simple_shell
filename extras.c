#include "shell.h"

/**
* myexecve - executes commands
* @commands: array of commands
* @count: number of executions
* @program_name: program_name
* Return: exit status of execve
*/
int myexecve(char *commands[], int *count, char **program_name)
{
	char str[100];
	int i = 0;
	int status = 0;
	pid_t pid;
	
	/*checks if first character of first item in commands array is '/'(is in-built comand) and copies the command to str */
	if (commands[0][0] == '/')
	{
		strcpy(str, commands[0]);
	} 
	/*concatenates first item of commands array with "/bin/" to make it executable */
	else
	{
		/* copies "/bin/" to str */
		strcpy(str, "/bin/");
		/* concats str with first item in commands */
		strcat(str, commands[0]);
	}
	if (check_command(commands, program_name, count) == -1)
	{
		/*frees items in commands[] while commands are less than 10 and command is not null */
		for (i = 0; i < 10 && commands[i] != NULL; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}
		return (127);
	} else
	{
		/*creates a child process and assigns its PID to pid */
		pid = fork();
		/*checks if creating child process failed*/
		if (pid == -1)
		{
			perror(myprogram_name);
			write(STDOUT_FILENO, "fork\n", 5);
		}
		/*checks if child process was successfuly created and calls execve() */
		else if (pid == 0)
		{
			/*executes commands in commands[] with str as path and exits if execution is not success */
			if (execve(str, commands, environ) == -1)
			{
				perror(myprogram_name);
			}
		} 
		/*parent process saves exit status of child process with PID pid to status */
		else
		{
			waitpid(pid, &status, 0);

		}
		/*frees items in commands[] while commands are less than 10 and command is not null */
		for (i = 0; i < 10 && commands[i] != NULL; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}
		/*returns exit status of the created child process */
		return (status);
	}
}

/**
* _parser - parse commands
* @head: pointer to head of a linked list
* @count: number of executions
* @program_name: program_name
* Return: nothing
*/
void _parser(Node **head, int *status, int *count, char **program_name)
{
	char *echo_cmd = NULL;

	if (*head != NULL)
	{
		/*checks if linked list has second a second node*/
		if (strcmp((*head)->cmd, "echo") == 0 &&(*head)->next != NULL)
		{
			/*duplicates command in the second node to echo_cmd*/
			echo_cmd = strdup((*head)->next->cmd);
		}
	
		/*checks if command in the first Node is "exit" and calls myexit() to handle the command*/
		if (strcmp((*head)->cmd, "exit") == 0)
		{
			myexit(head);
		}
		/*checks if command in the first Node is "env" and calls print_env() to handle the command*/
		else if (strcmp((*head)->cmd, "env") == 0)
		{
			print_env();
		}
		/*checks if command in the first Node is "cd" and calls mycd() to handle the command*/ 
		else if (strcmp((*head)->cmd, "cd") == 0)
		{
			mycd(head);
		}
		/*checks if command in the first Node is either "setenv" or "unsetenv" and calls myenv() to handle the command*/
		else if (strcmp((*head)->cmd, "setenv") == 0 || strcmp((*head)->cmd, "unsetenv") == 0)
		{
	
			myenv(head);
		}
		/*checks if command in the first Node is "echo" AND second node is available with command that starts with "$" and 				calls var_replace() to 			handle the command*/
		else if (strcmp((*head)->cmd, "echo") == 0 && echo_cmd != NULL && echo_cmd[0] == '$')
		{
			var_replace(head, status);
		}
	 
		else
		/*default function command_alloc() is called to take care of other commands*/
		{
			command_alloc(head, status, count, program_name);
	
		}
		/*checks if echo_cmd is not null and frees it*/
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
void _mycd(char *temp[], int i, char **current_wd, char **current_dir, size_t dir_len)
{
	/*checks if the first item in temp[] is "cd"*/
	if (strcmp(temp[0], "cd") == 0)
	{
		/*checks if temp[] has only one item which is "cd"*/
		if (i == 1)
		{
			/*changes directory to value of "HOME" */
			chdir(_getenv("HOME"));
			/*gets cwd and assigns it to current_wd*/
			*current_wd = getcwd(*current_dir, dir_len);
			/*updates "OLDPWD" to current_wd*/
			setenv("OLDPWD", *current_wd, 1);
			/*updates "PWD" to current_wd*/
			setenv("PWD", *current_wd, 1);
		}
		/*chacks if temp[] has two items and the second item is '-'*/
		else if (i == 2 && strcmp(temp[1], "-") == 0)
		{

			/*changes directory to OLDPWD*/
			chdir(_getenv("OLDPWD"));
			/*assigns cwd to current)wd*/
			*current_wd = getcwd(*current_dir, dir_len);
			/*updates "OLDPWD" to previous "PWD"*/
			setenv("OLDPWD", _getenv("PWD"), 1);
			/*updates "PWD" to current_wd*/
			setenv("PWD", *current_wd, 1);
		}
		/*checks if temp[] has 2 items*/
		else if (i == 2)
		{
			/*change dir to second item*/
			chdir(temp[1]);
			/*get cwd and save it to a variable*/
			*current_wd = getcwd(*current_dir, dir_len);
			/*update PLDPWD  to previous PWD*/
			setenv("OLDPWD", _getenv("PWD"), 1);
			/*updates PWD to cwd*/
			setenv("PWD", *current_wd, 1);
		}
		else
		{
			write(STDERR_FILENO, "cd", 2);
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
	if (strspn(*buffer, " \t\n\r") == strlen(*buffer))
	{
		free(*buffer);
		exit(0);
	}
}
	

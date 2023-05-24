#include "shell.h"

void print_pid(Node **head)
{
	Node *list = (*head)->next;
	char *str = malloc(20);
	int pid = (int)(getpid());

	if (_strcmp(list->cmd, "$$") == 0)
	{
		char *pid_str = itoa(pid, str);
		
		write(STDOUT_FILENO, pid_str, _strlen(pid_str));
		if (list->next != NULL)
		{
			write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, list->next->cmd, _strlen(list->next->cmd));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
			write(STDOUT_FILENO, "\n", 1);
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}



void print_status(Node **head, int *status)
{
	Node *list = (*head)->next;

	if (_strcmp(list->cmd, "$?") == 0)
	{
		char *str = malloc(20);
		char *status_str = itoa(*status, str);


		write(STDOUT_FILENO, status_str, _strlen(status_str));
		if (list->next != NULL)
		{
			write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, list->next->cmd, _strlen(list->next->cmd));
			write(STDOUT_FILENO, "\n", 1);
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		free_item(str);
	}
}

void malloc_error(char *buff)
{
	if (buff == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

void read_error(int num_read)
{
	if (num_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
}

void free_commands(char **commands)
{
	int i;

	for (i = 0; i < 10 && commands[i] != NULL; i++)
	{
		free(commands[i]);
		commands[i] = NULL;
	}
}

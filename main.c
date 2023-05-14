#include "shell.h"

/**
* append - appends a struct to a linked list
* @head: pointer to a linked list
* @command: command string to append
* Return: nothing
*/
void append(Node **head, char *cmd)
{
	Node *new_list = malloc(sizeof(Node));

	
	if (new_list == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	new_list->cmd = strdup(cmd);
	new_list->next = NULL;
	if (*head == NULL)
	{
		*head = new_list;
	}	
	else
	{
		while ((*head)->next != NULL)
		{
			head = &(*head)->next;
		}
		(*head)->next = new_list;
	}
}

/**
* free_list - frees linked list
* @head: pointer to head of the list
* Return: void
*/
void free_list(Node **head)
{
	Node *temp = NULL;
	
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->cmd);
		free(temp);
	}
	*head = NULL;
}
/**
* _interactive - executes commands on interactive mode
* @head: pointer to head of a linked list
* @buffer: pointer to buffer
* @no_read: pointer to no_read
* @chars: chars read
* Return: void
*/
void _interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars)
{
	size_t n = -1;
	
	write(STDOUT_FILENO, "$ ", 1+1);
	while(((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		if (strspn(*buffer, " \t\n\r") == strlen(*buffer))
			write(STDOUT_FILENO, "$ ", 1+1);
		else
		{
			(*buffer)[strcspn((*buffer), "\n")] = '\0';
			*token = strtok(*buffer, " ");
			while(*token != NULL)
			{
				append(head, *token);
				*token = strtok(NULL, " ");
			}
			_parser(head);
			if (*head != NULL)
			{
				free_list(head);
				*head = NULL;
			}
			if (*token != NULL)
			{
				free(*token);
				*token = NULL;
			}
			if (*buffer != NULL)
			{
				free(*buffer);
				*buffer = NULL;
			}
			write(STDOUT_FILENO, "$ ", 1+1);
		}
	}
}

/**
* _non_interactive - executes commands on non_interactive mode
* @head: pointer to head of a linked list
* @buffer: pointer to buffer
* @no_read: pointer to no_read
* @chars: chars read
* Return: void
*/
void _non_interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars)
{
	size_t n = -1;
	
	while (((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		_whitespace(buffer);
		(*buffer)[strcspn(*buffer, "\n")] = '\0';
		*token = strtok(*buffer, " ");
		while (*token != NULL)
		{
			append(head, *token);
			*token = strtok(NULL, " ");
		}
		_parser(head);
		free_head(head);
		if (*token != NULL)
		{
			free(*token);
			*token = NULL;
		}
		if (*buffer != NULL)
		{
			free(*buffer);
		*buffer = NULL;
		}

	}
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

/**
* main - executes commands
* @ac: ac
* @av: av
* Return: 0 on success
*/

int main(void)
{
	size_t no_read = 0, chars = 0;
	char *buffer = NULL;
	char *token = NULL;
	Node *head = NULL;
		
	if (isatty(STDIN_FILENO) == 1)
	{
		_interactive(&head, &buffer, &token, &no_read, &chars);
	} else
	{
		_non_interactive(&head, &buffer, &token, &no_read, &chars);
	}
	return (0);
}

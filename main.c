#include "shell.h"


/**
* append - appends a struct to a linked list
* @head: pointer to a linked list
* @cmd: command string to append
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
	new_list->cmd = _strdup(cmd);
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
		if (temp->cmd != NULL)
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
* @token: pointer to token
* @list: list of executables
* @program_name: program_name
* @path: path
* Return: void
*/
void _interactive(Node **head, char **buffer, char **token,
		size_t *no_read, size_t *chars, char **program_name, char **list, char *path)
{
	size_t n = -1;
	int status = 0;
	int count = 1;

	write(STDOUT_FILENO, "$ ", 2);
	while (((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		if (_strcspn(*buffer, " \t\n\r") == _strlen(*buffer))
			write(STDOUT_FILENO, "$ ", 2);
		else
		{
			(*buffer)[_strcspn((*buffer), "\n")] = '\0';
			*token = strtok(*buffer, " ");
			while (*token != NULL && _strcmp(*token, "#") != 0)
			{

				append(head, *token);
				*token = strtok(NULL, " ");

			}
			if (*buffer != NULL)
			{
				free(*buffer);
				*buffer = NULL;
			}
			_parser(head, &status, &count, program_name, list, path);
			write(STDOUT_FILENO, "$ ", 2);
			free_head(head);

		}
		count++;
	}
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

/**
* _non_interactive - executes commands on non_interactive mode
* @head: pointer to head of a linked list
* @buffer: pointer to buffer
* @no_read: pointer to no_read
* @chars: chars read
* @token: pointer to token
* @list: list of executables
* @program_name: program  name
* @path: path
* Return: void
*/
void _non_interactive(Node **head, char **buffer, char **token,
	size_t *no_read, size_t *chars, char **program_name, char **list, char *path)
{
	size_t n = -1;
	int status = 0, count = 1;

	while (((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		_whitespace(buffer);
		(*buffer)[_strcspn(*buffer, "\n")] = '\0';
		*token = strtok(*buffer, " ");
		while (*token != NULL)
		{
			append(head, *token);
			*token = strtok(NULL, " ");
		}
		if (*buffer != NULL)
		{
			free(*buffer);
			*buffer = NULL;
		}
		_parser(head, &status, &count, program_name, list, path);
		free_head(head);
		if (*token != NULL)
		{
			free(*token);
			*token = NULL;
		}
		count++;
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
int main(int ac, char *av[])
{
	size_t no_read = 0, chars = 0;
	char *buffer = NULL;
	char *token = NULL, *path = _getenv("PATH");
	Node *head = NULL;
	char *_path = _strdup(path);
	char *program_name = av[0];
	char *list[5000] = {NULL};

	_executables(list, &_path);
	free(_path);

	if (ac == 2)
	{
		struct stat file;

		if (stat(av[1], &file) == -1)
		{
			perror(" stat");
			exit(EXIT_FAILURE);
		}
		else
			_file(&head, av[1], &program_name, list, path);

	}
	else
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			_interactive(&head, &buffer, &token, &no_read,
					&chars, &program_name, list, path);
		}
		else
		{
			_non_interactive(&head, &buffer,
					&token, &no_read, &chars, &program_name, list, path);
		}
	}
	clean_list(list);
	return (0);
}

#include "shell.h"

/**
* execute_file - executes commands in fd
* @head: pointer to linked list
* @fd: fd
* @list: list of executables
* @program_name: program_name
* Return: void
*/

void execute_file(Node **head, int fd, char **program_name, char **list)
{
	char *line, *token, *temp;
	ssize_t num_read;
	char *tokens[100];
	int status = 0, i = 0;
	int count = 1;
	char *buff = malloc(sizeof(char) * 1024);

	if (buff == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_execute_file(head, &num_read, &buff, &line, tokens,
			&temp, &fd, &status, &count, &token, program_name, list);
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(buff);
	if (num_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
}

/**
* _file - handles file command line argument
* @head: pointer to head of linked list
* @filename: filename
* @program_name: program_name
* @list: list of executables
* Return: nothing
*/
void _file(Node **head, char *filename, char **program_name, char **list)
{
	int fd;


	/*checks if user has access permission*/
	if (access(filename, R_OK) != 0)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
	/*open file in readonly mode*/
	fd = open(filename, O_RDONLY);
	/*check if file was opened successfully*/
	if (fd == -1)
	{
		perror("fd");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		execute_file(head, fd, program_name, list);
		break;
	}
	/*checks if file is closed successfullly*/
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}


/**
*_execute_file - helper function to execute_file
* @head: pointer to linked list
* @program_name: program name
* @num_read: number read
* @buff: buffer
* @line: line
* @tokens: tokens array
* @token: token
* @temp: temp var
* @fd: file descriptor
* @list: list of executables
* @status: exit status
* @count: execution counts
* Return: void
*/
void _execute_file(Node **head, ssize_t *num_read, char **buff,
		char **line, char **tokens, char **temp, int *fd, int *status,
			int *count, char **token, char **program_name, char **list)
{
	int j, i;

	while ((*num_read = read(*fd, buff, 1024)) > 0)
	{
		buff[*num_read] = '\0';
		_whitespace(buff);
		*line = strtok(*buff, "\n");
		while (line != NULL)
		{
			tokens[i++] = _strdup(*line);
			*line = strtok(NULL, "\n");
		}
		tokens[i] = NULL;
		j = 0;
		while (tokens[j] != NULL && j < i)
		{
			*temp = _strdup(tokens[j]);
			*token = strtok(*temp, " ");
			while (token != NULL)
			{
				append(head, *token);
				*token = strtok(NULL, " ");
			}
			if (temp != NULL)
			{
				free(temp);
				temp = NULL;
			}
			_parser(head, status, count, program_name, list);
			free_head(head);
			j++;
			count++;
		}
	}
}

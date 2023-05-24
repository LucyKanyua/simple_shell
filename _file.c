#include "shell.h"

/**
* _file - handles file command line argument
* @head: pointer to head of linked list
* @filename: filename
* @program_name: program_name
* @list: list of executables
* @path: path
* Return: nothing
*/
void _file(Node **head, char *filename,
		char **program_name, char **list, char *path)
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
		execute_file(head, fd, program_name, list, path);
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
* execute_file - executes commands in fd
* @head: pointer to linked list
* @fd: fd
* @program_name: program_name
* @list: list of executables
* @path: path
* Return: void
*/

void execute_file(Node **head, int fd,
		char **program_name, char **list, char *path)
{
	ssize_t num_read;
	char *tokens[100] = {NULL};
	int status = 0, i = 0, j = 0, count = 1;
	char *line = NULL, *token = NULL;
	char *temp = NULL, *buff = malloc(sizeof(char) * 1024);

	malloc_error(buff);
	while ((num_read = read(fd, buff, 1024)) > 0)
	{
		buff[num_read] = '\0';
		_whitespace(&buff);
		line = strtok(buff, "\n");
		while (line != NULL)
		{
			tokens[i++] = strdup(line);
			line = strtok(NULL, "\n");
		}
		tokens[i] = NULL;
		j = 0;
		while (tokens[j] != NULL && j < i)
		{
			temp = strdup(tokens[j]);
			token = strtok(temp, " ");
			while (token != NULL)
			{
				append(head, token);
				token = strtok(NULL, " ");
			}
			free_item(temp);
			_parser(head, &status, &count, program_name, list, path);
			free_head(head);
			j++;
			count++;
		}
	}
	free_token(tokens, i);
	free(buff);
	read_error(num_read);
}

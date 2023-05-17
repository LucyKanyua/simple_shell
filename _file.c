#include "shell.h"

void execute_file(Node **head, int fd)
{
	char *line, *token, *temp;
	ssize_t num_read;
	char *tokens[100];
	int status = 0, i = 0, j= 0;
	pid_t pid = getpid();
	/*allocates mamory for buff*/
	char *buff = malloc(sizeof(char) * 1024);
	
	/*checks if mem allocation was success*/
	if (buff == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	/*while reading from fd is successful*/
	while ((num_read = read(fd, buff, 1024)) > 0)
	{
		/*terminate content read with null character*/
		buff[num_read] = '\0';
		
		/*handles the case when only white space is read*/
		_whitespace(&buff);
		/*tokenizes contents of buff with '\n' as delimiter and stores tokens to line*/
		line = strtok(buff, "\n");
		
		while (line != NULL)
		{
			/*duplicates content of line to tokens[]*/
			tokens[i++] = strdup(line);
			line = strtok(NULL, "\n");
		}
		/*assigns last item of tokens[] to null*/
		tokens[i] = NULL;
		/*assigns 0 to j so that it will always start at 0 in each iteration*/
		j = 0;
		
		/*iterates tokens[] duplicating to temp and executing each line before advancing to next line in tokens[]*/ 
		while (tokens[j] != NULL && j < i)
		{
			/*duplicates token at index j of tokens[] to temp*/
			temp = strdup(tokens[j]);
			/*tokenizes each token in temp using " " as delimiter*/
			token = strtok(temp, " ");
			while (token != NULL)
			{
				/*calls append() to append token to the linked list*/
				append(head, token);
				token = strtok(NULL, " ");
			}
			/*free temp so that next iteration will find it null*/
			if (temp != NULL)
			{
				free(temp);
				temp = NULL;
			}
			/*call _parse() to take care of commands in the linked list*/
			_parser(head, &status, &pid);
			/*free linked list*/
			free_head(head);
			/*increment j to advance to the next line in tokens[] during next iteration*/
			j++;
		}
	}
	/*free tokens[]*/
	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(buff);
	/*checks if reading was not succes*/
	if (num_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
}

/**
* _file - handles file command line argument
* @filename: filename
* Return: nothing
*/
void _file(Node **head, char *filename)
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
	/*call execure_file to operate on contents of the file and break the loop on its return*/
	while (1)
	{
		execute_file(head, fd);
		break;
	}
	/*checks if file is closed successfullly*/
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}
	

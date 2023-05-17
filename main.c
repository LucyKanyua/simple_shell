#include "shell.h"

char *myprogram_name;

/**
* append - appends a struct to a linked list
* @head: pointer to a linked list
* @command: command string to append
* Return: nothing
*/
void append(Node **head, char *cmd)
{	
	/*allocates memory and declares a new node*/
	Node *new_list = malloc(sizeof(Node));

	/*checks if mem allocation failed*/
	if (new_list == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	/*duplicates string to Node*/
	new_list->cmd = strdup(cmd);
	/*makes Node to pint to NULL*/
	new_list->next = NULL;
	/*checks if head is pointing to NULL and makes it point to created Node*/
	if (*head == NULL)
	{
		*head = new_list;
	}	
	else
	{
		/*if head is not pointing to null, new_list(Node) is appended to it*/
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
	/*declares a temporary Node*/
	Node *temp = NULL;
	

	/*checks if Node is not null and frees it*/
	while (*head!= NULL)
	{
		temp = *head;
		*head = (*head)->next;
		if (temp->cmd != NULL)
			free(temp->cmd);
		free(temp);
	}
	/*assigns head pointer to null after its freed*/
	*head = NULL;

}
/**
* _interactive - executes commands on interactive mode
* @head: pointer to head of a linked list
* @buffer: pointer to buffer
* @no_read: pointer to no_read
* @chars: chars read
* @program_name: program_name
* Return: void
*/
void _interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars, char **program_name)
{
	size_t n = -1;
	int status = 0;
	int count = 1;
	
	/*prompts*/
	write(STDOUT_FILENO, "$ ", 1+1);
	/*reads characters of size chars from stdin till '\n' is encountered and stores them in buffer*/
	while(((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		/*checks if whitespace is entered and prompts agin*/
		if (strspn(*buffer, " \t\n\r") == strlen(*buffer))
		{
			write(STDOUT_FILENO, "$ ", 1+1);
		}
		/*goes ahead to execute command entered*/
		else
		{
			
			/*replaces "\n" in buffer with "\0"*/
			(*buffer)[strcspn((*buffer), "\n")] = '\0';
			/*tokenizes buffer  with " " as delimiter*/
			*token = strtok(*buffer, " ");
			while(*token != NULL && strcmp(*token, "#") != 0)
			{
				/*appends each token to linked list*/
				append(head, *token);
				*token = strtok(NULL, " ");

			}
			
			/*checks if buffer is not null and frees it*/
			if (*buffer != NULL)
			{
				free(*buffer);
				*buffer = NULL;
			}
			
			
			/*parses commands in the linked list and calls various functions to execute them*/
			_parser(head, &status, &count, program_name);
			write(STDOUT_FILENO, "$ ", 1+1);
			
			if (*head != NULL)
			{
				free_list(head);
				*head = NULL;
			}

		}
		count++;
	}
	/*checks if there could be unsuccesful read by getline and frees buffer again*/
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
 @program_name: program_name
* Return: void
*/
void _non_interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars, char **program_name)
{
	size_t n = -1;
	int status = 0;
	int count = 1 ;
	
	/*reads characters of size chars from stdin till '\n' is encountered and stores them in buffer*/
	while (((*no_read) = getline(buffer, chars, stdin)) != n)
	{
		/*handles case where only whitespace is pipped*/
		_whitespace(buffer);

		/*replaces "\n" in buffer with "\0"*/
		(*buffer)[strcspn(*buffer, "\n")] = '\0';
		/*tokenizes buffer  with " " as delimiter*/
		*token = strtok(*buffer, " ");
		while (*token != NULL)
		{
			/*appends each token to linked list*/
			append(head, *token);
			*token = strtok(NULL, " ");
		}
		
		/*checks if buffer is not null and frees it*/
		if (*buffer != NULL)
		{
			free(*buffer);
			*buffer = NULL;
		}
		
		
		/*parses commands in the linked list and calls various functions to execute them*/
		_parser(head, &status, &count, program_name);
		/*calls free_head() which frees linked list*/
		free_head(head);
		/*checks if token is not null and frees it*/
		if (*token != NULL)
		{
			free(*token);
			*token = NULL;
		}
		count++;
		

	}
	/*checks if there could be unsuccesful read by getline and frees buffer again*/
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
	char *token = NULL;
	Node *head = NULL;
	char *program_name = av[0];
	
	
	
	/*checks if the program was run with one argument and handles second argument approprietly*/
	if (ac == 2)
	{
		/*declares struct file of type stat*/
		struct stat file;
		/*checks if the second argument is not file and exits with eror mwssage*/
		if (stat(av[1], &file) == -1)
		{
			perror(" stat");
			exit(EXIT_FAILURE);
		}
		/*calls _file() that handles second arguments approprietly*/
		 else
		{

			_file(&head, av[1], &program_name);
		}

	}
	/*if argument pased is one takes care of the command passed*/
	else
	{
		/*checks if input stream is std input and calls _interactive()*/
		if (isatty(STDIN_FILENO) == 1)
		{
			_interactive(&head, &buffer, &token, &no_read, &chars, &program_name);
		}
		/*if input stream is not stdin _non_interactive() is called*/
		else
		{
			_non_interactive(&head, &buffer, &token, &no_read, &chars, &program_name);
		}
	}
	return (0);
}

#include "shell.h"

/**
* check_operator - checks opeartor present in the command passed
* @head: pointer to head pointer of a linked list
* Return: pointer to string
*/
char *check_operator(Node **head)
{

	Node *temp = *head;
	
	while (temp != NULL)
	{
		if (strcmp(temp->cmd, ";") == 0)
		{
			return(";");
		} else if (strcmp(temp->cmd, "||") == 0)
		{
			return("||");
		} else if (strcmp(temp->cmd, "&&") == 0)
		{
			return("&&");
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
* command_alloc - allocates commands to helper functions
* @head: pointer to head of a linked list
* Return: nothing
*/
void command_alloc(Node **head)
{
	int status = 0;

	char *operator = check_operator(head);
	
	if (operator == NULL)
	{
		execute(head, status);
	} else if (strcmp(operator, ";") == 0)
	{
		_command_separator(head, status);
	} else if (strcmp(operator, "||") == 0)
	{
		printf("caliing or\n");
	} else if (strcmp(operator, "&&") == 0)
	{
		printf("calling and\n");
	}

}

/**
* execute - executes command
* @head: pointer to head of a linked list
* @status: exit status of the previous program
* Return: nothing
*/
void execute(Node **head, int status)
{

	char *commands[10];
	Node *temp = *head;
	int i = 0;

	
	while (temp != NULL)
	{
		commands[i++] = strdup(temp->cmd);
		temp = temp->next;
	}
	commands[i] = NULL;
	i = 0;
	
	myexecve(commands, status);
}

/**
* _command_separator - executes commands with command separator
* @head: pointer to head of linked list
* @status: exit status of previous process
*/
void _command_separator(Node **head, int status)
{
	Node *temp = *head;
	char *commands[10] = {NULL};
	int i = 0;

	
	while (temp != NULL)
	{
		if (strcmp(temp->cmd, ";") == 0)
		{
			if (commands[0] != NULL)
			{
				myexecve(commands, status);
			}

			i = 0;
		} else
		{
			commands[i] = strdup(temp->cmd);
			i++;
		}
		temp = temp->next;
	}
	
	if (commands[0] != NULL)
	{
		myexecve(commands, status);
	}
}
/**
* _exit - handles exit command
* @head: pointer to head of a linked list
* Return: void
*/
void myexit(Node **head)
{
	Node *status = (*head)->next;
	int exit_status = 0;
	char exit_status_str[16];
	
	if ((*head)->next == NULL)
	{
		exit(0);
	} else
	{
		strcpy(exit_status_str, status->cmd);
		exit_status_str[strlen(exit_status_str)] = '\0';
		exit_status = atoi(exit_status_str);
		exit(exit_status);
	}
}
		
	
		


























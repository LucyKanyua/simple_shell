#include "shell.h"

/**
* check_operator - checks opeartor present in the command passed
* @head: pointer to head pointer of a linked list
* Return: pointer to string
*/
char *check_operator(Node **head)
{
	/*creates reference to head of linked list*/
	Node *temp = *head;
	
	/*iterates linked list untill there are no more nodes*/
	while (temp != NULL)
	{
		/*checks if ";" is present in the node and returns ";" */
		if (strcmp(temp->cmd, ";") == 0)
		{
			return(";");
		}
		/*checks if "||" is present in the node and returns "||" */
		else if (strcmp(temp->cmd, "||") == 0)
		{
			return("||");
		}
		/*checks if "&&" is present in the node and returns "&&" */
		else if (strcmp(temp->cmd, "&&") == 0)
		{
			return("&&");
		}
		/* assigns temp to point to the next node */
		temp = temp->next;
	}
	/*returns null if no opeartor is found*/
	return (NULL);
}

/**
* command_alloc - allocates commands to helper functions
* @head: pointer to head of a linked list
* @count: number of executions
* @program_name: program_name
* Return: nothing
*/
void command_alloc(Node **head, int *status, int *count, char **program_name)
{
	/*assigns result of check_operator() to operator */
	char *operator = check_operator(head);
	*status = 10;
	
	/*operator is null default execute() is called*/
	if (operator == NULL)
	{
		execute(head, status, count, program_name);

	}
	/*if operator is ';' _command_separator() is called to take care of the command */ 
	else if (strcmp(operator, ";") == 0)
	{
		_command_separator(head, status, count, program_name);
	}
	/*if operator is "||" _or() is called to take care of the command*/ 
	else if (strcmp(operator, "||") == 0)
	{
		_or(head, status, count, program_name);
	}
	/*if operator is "&&" _and() is called to take care of the command*/  
	else if (strcmp(operator, "&&") == 0)
	{
		_and(head, status, count, program_name);
	}

}

/**
* execute - executes command
* @head: pointer to head of a linked list
* @status: exit status of the previous program
* @count: number of executions
* @program_name: program_name
* Return: nothing
*/
void execute(Node **head, int *status, int *count, char **program_name)
{

	char *commands[10];
	/*creates refrence to head*/
	Node *temp = *head;
	int i = 0;

	/*interates linked list till there are no more nodes*/
	while (temp != NULL)
	{
		/*duplicates command in the current node to array commands*/
		commands[i++] = strdup(temp->cmd);
		/*assigns current to point to the next node*/
		temp = temp->next;
	}
	/*assigns last element of commands array to null*/
	commands[i] = NULL;
	i = 0;
	
	/*calls myexecve() to execute commands in the commands array and assigns exit of the child process to status*/
	*status = myexecve(commands, count, program_name);
}

/**
* _command_separator - executes commands with command separator ';'
* @head: pointer to head of linked list
* @status: exit status of previous process
* @count: number of executions
* @program_name: program_name
* Return: void
*/
void _command_separator(Node **head, int *status, int *count, char **program_name)
{
	Node *temp = *head;
	char *commands[10] = {NULL};
	int i = 0;

	/*interates linked list till there are no more nodes*/
	while (temp != NULL)
	{
		/*if current node has command of ';' commands in the array are executed*/
		if (strcmp(temp->cmd, ";") == 0)
		{
			/*checks if commands array is not empty*/
			if (commands[0] != NULL)
			{
				/*calls myexecve() to execute commands in the commands array and assigns exit of the child process to status*/
				*status = myexecve(commands, count, program_name);
			}

			i = 0;
		} 
		/*if current node does not have ';', the command in the current node is added to commands array*/
		else
		{
			/*duplicated command in the current node to commands array*/
			commands[i] = strdup(temp->cmd);
			i++;
		}
		/*assigns current node to point to next node*/
		temp = temp->next;
	}
	/*checks if there is command in the aray that was left unexecuted*/
	if (commands[0] != NULL)
	{
		/*calls myexecve() to execute commands in the commands array and assigns exit of the child process to status*/
		*status = myexecve(commands, count, program_name);
	}
}
/**
* _exit - handles exit command
* @head: pointer to head of a linked list
* Return: void
*/
void myexit(Node **head)
{
	/*assigns node status to point to second node of the linked list*/
	Node *status = (*head)->next;
	int exit_status = 0;
	char exit_status_str[16];
	
	/*checks if linked list has only one node and exits with status 0*/
	if ((*head)->next == NULL)
	{
		/*free linked list*/
		free_head(head);
		exit(0);
	}
	/*exits with status in command part of second node which is now pointed to by Node status*/
	else
	{
		/*copies command in status node to exit_status_str*/
		strcpy(exit_status_str, status->cmd);
		/*terminates exit_status_str with '\0'*/
		exit_status_str[strlen(exit_status_str)] = '\0';
		/*coverts exit_status_str to int*/
		exit_status = atoi(exit_status_str);
		/*free linked list*/
		free_head(head);
		/*exits with status stored in exit_status*/
		exit(exit_status);
	}
}
		
	
		


























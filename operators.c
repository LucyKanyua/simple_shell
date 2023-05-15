#include "shell.h"

/**
* _or - handles logical operator OR
* @head: pointer to head of a linked list
* Return: void
*/
void _or(Node **head)
{
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0, status = -1;
	
	while (list != NULL)
	{
		if (strcmp(list->cmd, "||") != 0)
		{
			temp[i++] = strdup(list->cmd);
			temp[i] = NULL;
		}
		if (strcmp(list->cmd, "||") == 0 || list->next == NULL)
		{
			if (status != 0)
			{
				status = myexecve(temp);
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				i = 0;
			}
		}

		list = list->next;
	}
	
}


/**
* _and - handles logical operator AND
* @head: pointer to head of a linked list
* Return: void
*/
void _and(Node **head)
{
	Node *list = *head;
	char *temp[50];
	int i = 0, j = 0, status = 0;
	
	while (list != NULL)
	{
		if (strcmp(list->cmd, "&&") != 0)
		{
			temp[i++] = strdup(list->cmd);
			temp[i] = NULL;
		}
		if (strcmp(list->cmd, "&&") == 0 || list->next == NULL)
		{
			if (status == 0)
			{
				status = myexecve(temp);
				for (j = 0; j < i; j++)
				{
					if (temp[j] != NULL)
					{
						free(temp[j]);
						temp[j] = NULL;
					}
				}
				i = 0;
			}
		}

		list = list->next;
	}
	
}	

#include "shell.h"

/**
* _executables - finds executables
* @list: list to update
* @path: path
* Return: nothing
*/
void _executables(char **list, char **path)
{
	char *dir;
	char **dir_list = NULL;
	size_t i = 0, count = 1, k = 0, j = 0, len = strlen(*path);
	DIR *directory;
	struct dirent *entry;

	for (i = 0; i < len; i++)
	{
		if ((*path)[i] == ':')
			count++;
	}
	i = 0;
	dir_list = calloc(count + 1, sizeof(char *));
	dir = strtok(*path, ":");
	while (dir != NULL)
	{
		dir_list[i] = dir;
		dir = strtok(NULL, ":");
		i++;
	}
	dir_list[i] = NULL;
	for (j = 0; j < i && dir_list[j] != NULL; j++)
	{
		directory = opendir(dir_list[j]);
		if (directory == NULL)
		{
			perror("opendir");
			return;
		}
		while ((entry = readdir(directory)) != NULL)
		{
			list[k++] = strdup(entry->d_name);
		}
		if (closedir(directory) != 0)
			perror("closedir");
	}
	list[k] = NULL;
	free_dptr(dir_list);
	free_item(dir);
}

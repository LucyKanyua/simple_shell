#include "shell.h"

/**
 * _getcwd - searches environment var in environ and returns pointer
 * @name: name of the env
 * Return: pointer to the env
 */
char *_getenv(char *name)
{
	char **env = environ;
	char *entry;
	char *equals;
	size_t len;

	while (*env != NULL)
	{
		entry = *env;
		equals = strchr(entry, '=');

		if (equals != NULL)
		{
			len = equals - entry;
			if (strncmp(entry, name, len) == 0 && strlen(name) == len)
			{
				return (equals + 1);
			}
		}
		env++;
	}
	return (NULL);
}

/**
 * _setenv - sets env
 * @name: name
 * @value: value
 * @overwrite: overwrite
 * Return: int
 */
int _setenv(char *name, char *value, int overwrite) /*has bugs*/
{
	char **envp = environ;
	int name_len = strlen(name);
	char *env_var, *temp;
	int value_len = strlen(value);

	while (*envp != NULL)
	{
		env_var = *envp;
		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
		{
			if (!overwrite)
			{
				return (0);
			}
			temp = (char *) malloc(name_len + value_len + 2);
			if (!name)
				return (-1);
			name = temp;
			name[name_len] = '=';
			strncpy(&name[name_len + 1], value, value_len);
			name[name_len + value_len + 1] = '\0';
			*envp = name;
			
			return (0);
		}
		envp++;
	}
	temp = (char *) malloc(name_len + value_len + 2);
	if (!name)
		return (-1);
		
	name = temp;
	name[name_len] = '=';
	strncpy(&name[name_len + 1], value, value_len);
	name[name_len + value_len + 1] = '\0';
	 *envp = name;
	 *(envp + 1) = NULL;
	return (0);
}

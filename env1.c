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
int _setenv(char *name, char *value, int overwrite)
{
	char **envp = environ;
	int name_len = strlen(name);
	char *env_var, *new_env_var;
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
			new_env_var = (char *) malloc(name_len + value_len + 2);
			strncpy(new_env_var, name, name_len);
			new_env_var[name_len] = '=';
			strncpy(&new_env_var[name_len + 1], value, value_len);
			new_env_var[name_len + value_len + 1] = '\0';
			*envp = new_env_var;
			
			free(new_env_var);
			new_env_var = NULL;
			return (0);
		}
		envp++;
	}
	new_env_var = (char *) malloc(name_len + value_len + 2);
	strncpy(new_env_var, name, name_len);
	new_env_var[name_len] = '=';
	strncpy(&new_env_var[name_len + 1], value, value_len);
	new_env_var[name_len + value_len + 1] = '\0';
	 *envp = new_env_var;
	 *(envp + 1) = NULL;
	 free(new_env_var);
	 new_env_var = NULL;

	return (0);
}

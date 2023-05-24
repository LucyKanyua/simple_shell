#include "shell.h"

/**
 * _getenv - searches environment var in environ and returns pointer
 * @name: name of the env
 * Return: pointer to the env value
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
		equals = _strchr(entry, '=');

		if (equals != NULL)
		{
			len = equals - entry;
			if (_strncmp(entry, name, len) == 0 && _strlen(name) == len)
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
		if (_strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
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
			_strncpy(&name[name_len + 1], value, value_len);
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
	_strncpy(&name[name_len + 1], value, value_len);
	name[name_len + value_len + 1] = '\0';
	 *envp = name;
	 *(envp + 1) = NULL;
	return (0);
}

/**
* check_command - checks if command passed is valid
* @commands: commands to be checked
* @program_name: program name
* @count: number of executed commands
* @list: list of executables
* Return: 0 if command is valid otherwise -1
*/
int check_command(char *commands[],
		char **program_name, int *count, char **list)
{
	char bin[10] = "/bin/";
	char *_bin = NULL;
	int valid = 0, i = 0, len = 0;



	while (list[i] != NULL)
	{
		if (commands[0][0] == '/' && strncmp(commands[0], bin, 5) == 0)
		{
			len = strlen(commands[0]);
			_bin = strndup(commands[0] + 5, len - 4);
		}
		if (_strcmp(list[i], commands[0]) == 0 ||
			(_bin != NULL && strcmp(list[i], _bin) == 0))
			valid = 1;
		i++;
		if (_bin != NULL)
			free(_bin);
	}
	i = 0;

	return (print_error(valid, program_name, count, commands));

	return (0);
}

/**
* itoa - converts int to string
* @num: int to be converted
* @str: pointer to the converted value
* Return: pointer to converted vakue
*/
char *itoa(int num, char *str)
{

	int j, k, i = 0;
	/*creates sign flag and assigns it to -1 if num < 0 or 1 if num > 0*/
	int sign = num < 0 ? -1 : 1;
	/*absolute value of num*/
	num = sign * num;

	if (num == 0)
	{
		str[i++] = 0 + '0';
	}
	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	}
	/*if num is negative '-' is appended at the end of the string*/
	if (sign == -1)
	{
		str[i++] = '-';
	}
	/*terminates str with null byte*/
	str[i] = '\0';

	/*reverses the string*/
	for (j = 0, k = i - 1; j < k; j++, k--)
	{
		char temp = str[j];

		str[j] = str[k];
		str[k] = temp;
	}

	return (str);
}

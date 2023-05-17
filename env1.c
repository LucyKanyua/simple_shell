#include "shell.h"

/**
 * _getcwd - searches environment var in environ and returns pointer
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

/**
* check_command - checks if command passed is valid
* @commands: commands to be checked
* @program_name: program name
* @count: number of executed commands
* Return: 0 if command is valid otherwise -1
*/
int check_command(char *commands[], char **program_name, int *count)
{
	char *list[] = {"ls", "/bin/ls", "/bin/pwd", "exit", "env", "setenv", "unsetenv", "cd", "echo", "pwd", NULL};
	int i = 0;
	int valid = 0;
	/*creates a copy of the command name*/
	char *temp = strdup(*program_name);
	char *str = malloc(100);
	/*converts count to string*/
	char *num_str = itoa(*count, str);
	
	
	
	/*checks command is available in commands and updates valid to 1*/
	while (list[i] != NULL)
	{
		if (strcmp(list[i], commands[0]) == 0)
			valid = 1;
		i++;
	}
	i = 0;
	/*if command is not available*/
	if (valid == 0)
	{
		write(STDERR_FILENO, temp, strlen(temp));
		write(STDERR_FILENO, " : ", 3);
		write(STDERR_FILENO, num_str, strlen(num_str));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, commands[0], strlen(commands[0]));
		write(STDERR_FILENO, " :", 2);
		write(STDERR_FILENO, " not found\n", 11);
		
		if (temp != NULL)
			free(temp);
		if (str != NULL)
			free(str);


		return (-1);

	}


	if (temp != NULL)
		free(temp);
	if (str != NULL)
		free(str);
	return (0);
}
	
/**
* itoa - converts int to string
* @num:" int to be converted
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
    
   
	/*converts each digit to char and appends to str*/
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
	
	
	
	
	
	
	
	
	
	

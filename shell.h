#ifndef SHELL_H
#define SHELL_H

#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

/**
* struct Node - struct
* @cmd: to hold commands
* @next: nexet Node
*
* Description: Node of a linked list
*/
typedef struct Node
{
	char *cmd;
	struct Node *next;
} Node;

extern char **environ;


char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *src);
size_t _strlen(char *src);
size_t _strcspn(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strncpy(char *dest, char *src, size_t n);
char *_strchr(char *str, int c);
void append(Node **head, char *cmd);
void free_list(Node **head);
void _interactive(Node **head, char **buffer, char **token,
		size_t *no_read, size_t *chars, char **program_name, char **list, char *path);
void _non_interactive(Node **head, char **buffer, char **token,
		size_t *no_read, size_t *chars, char **program_name, char **list, char *path);
char *check_operator(Node **head);
void command_alloc(Node **head, int *status,
	int *count, char **program_name, char **path);
void execute(Node **head, int *status,
		int *count, char **program_name, char **path);
void _command_separator(Node **head, int *status,
		int *count, char **program_name, char **path);
void myexit(Node **head, char **list);
void myenv(Node **head);
int _unsetenv(char *name);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
void mycd(Node **head);
void print_env(void);
int myexecve(char *commands[], int *count, char **program_name, char **path);
void _parser(Node **head, int *status,
		int *count, char **program_name, char **list, char *path);
void _mycd(char *temp[], int i,
		char **current_wd, char **current_dir, size_t dir_len);
void free_head(Node **head);
void _whitespace(char **buffer);
void _or(Node **head, int *status, int *count,
		char **program_name, char **path);
void _and(Node **head, int *status, int *count,
		char **program_name, char **path);
void var_replace(Node **head, int *status, char *path);
void _file(Node **head, char *filename, char **program_name, char **list, char *path);
void execute_file(Node **head, int fd, char **program_name, char **list, char *path);
int check_command(char *commands[],
		char **program_name, int *count, char **path);
char *itoa(int num, char *str);
void _myfree_list(char **commands);
void _execute_file(Node **head, ssize_t *num_read,
		char **buff, char **line, char **tokens, char **temp, int *fd,
			int *status, int *count, char **token, char **program_name, char **list, char *path);
void _executables(char **list, char **path);
void clean_list(char **list);
int print_error(int valid, char **program_name, int *count, char *commands[]);
void free_item(char *str);
void free_dptr(char **dptr);
void print_pid(Node **Head);
void print_status(Node **head, int *status);
void malloc_error(char *buff);
void read_error(int num_read);
void free_commands(char **commands);
void free_token(char **tokens, int count);

#endif

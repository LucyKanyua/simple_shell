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
typedef struct Node {
	char *cmd; /*to hold commands*/
	struct Node *next; /*to point to the next node*/
} Node;

extern char **environ;

void append(Node **head, char *cmd);
void free_list(Node **head);
void _interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars);
void _non_interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars);
char *check_operator(Node **head);
void command_alloc(Node **head, int *status, pid_t *pid);
void execute(Node **head, int *status, pid_t *pid);
void _command_separator(Node **head, int *status, pid_t *pid);
void myexit(Node **head);
void myenv(Node **head);
int _unsetenv(char *name);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
void mycd(Node **head);
void print_env(void);
int myexecve(char *commands[], pid_t *pid);
void _parser(Node **head, int *status, pid_t *pid);
void _mycd(char *temp[], int i, char **current_wd, char **current_dir, size_t dir_len);
void free_head(Node **head);
void _whitespace(char **buffer);
void _or(Node **head, int *status, pid_t *pid);
void _and(Node **head, int *status, pid_t *pid);
void var_replace(Node **head, int *status);
void _file(Node **head, char *filename);
void execute_file(Node **head, int fd);

#endif

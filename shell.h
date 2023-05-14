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

typedef struct Node {
	char *cmd;
	struct Node *next;
} Node;

extern char **environ;

void append(Node **head, char *cmd);
void free_list(Node **head);
void _interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars);
void _non_interactive(Node **head, char **buffer, char **token, size_t *no_read, size_t *chars);
char *check_operator(Node **head);
void command_alloc(Node **head);
void execute(Node **head, int status);
void _command_separator(Node **head, int status);
void myexit(Node **head);
void myenv(Node **head);
int _unsetenv(char *name);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
void mycd(Node **head);
void print_env(void);
void myexecve(char *commands[], int status);
void _parser(Node **head);
void _mycd(char *temp[], int i, char **current_wd, char **current_dir, size_t dir_len);
void free_head(Node **head);
void _whitespace(char **buffer);

#endif

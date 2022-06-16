#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"
extern char **environ;

/**
 * struct s_data - struct that contains all relevant data on runtime
 * @av: list of argument
 * @input: cmd line inputs
 * @tokens: tokens of each separeted cmd
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */

typedef struct s_data
{
	char **av;
	char *input;
	char **tokens;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_d;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(shell_d *d_sh);
} builtin_t;

void free_data(shell_d *d_sh);
void set_data(shell_d *d_sh, char **av);
void start_shell(shell_d *d_sh);
char *rm_comment(char *input);
char *get_line(int *i_eof);
void assignto_line(char **cmd_line, size_t *n, char *buffer, size_t j);
ssize_t read_line(char **cmd_line, size_t *n, FILE *stream);
void go_next(sep_list **list_s, line_list **list_l, shell_d *d_sh);
int split_commands(shell_d *d_sh, char *input);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
char **get_token(char *input);
char *swap_char(char *input, int bool);
int get_err(shell_d *d_sh, int eval);
char *strcat_cd(shell_d *d_sh, char *msg, char *err, char *ver_str);
char *get_cd_err(shell_d *d_sh);
char *error404(shell_d *d_sh);
char *exit_error(shell_d *d_sh);
char *env_err(shell_d *d_sh);
char *path_126_err(shell_d *d_sh);
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_d *d_sh, char *input, int i, int bool);
int check_syntax_error(shell_d *d_sh, char *input);
int get_help(shell_d *d_sh);
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);
void check_env(r_var **h, char *in, shell_d *data);
int check_vars(r_var **h, char *in, char *st, shell_d *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_d *d_sh);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
void get_sigint(int sig);
int _strspn(char *s, char *accept);
void rev_string(char *s);
char *_strdup(const char *s);
int cmp_chars(char str[], const char *delim);
int _strlen(const char *s);
int _isdigit(const char *s);
char *_strtok(char str[], const char *delim);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
int is_cdir(char *path, int *i);
int exec_line(shell_d *d_sh);
char *_which(char *cmd, char **_environ);
int is_executable(shell_d *d_sh);
int check_error_cmd(char *dir, shell_d *d_sh);
int cmd_exec(shell_d *d_sh);
int cmp_env_name(const char *nenv, const char *name);
int _env(shell_d *d_sh);
char *copy_info(char *name, char *value);
char *_getenv(const char *name, char **_environ);
int _setenv(shell_d *d_sh);
void set_env(char *name, char *value, shell_d *d_sh);
int _unsetenv(shell_d *datash);
void cd_to_home(shell_d *datash);
void cd_previous(shell_d *datash);
void cd_to(shell_d *datash);
void cd_dot(shell_d *datash);
int cd_shell(shell_d *datash);
void free_line_list(line_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_sep_list(sep_list **head);
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_rvar_list(r_var **head);
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval);
int exit_shell(shell_d *d_sh);
int (*get_builtin(char *cmd))(shell_d *);

#endif

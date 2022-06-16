#include "main.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @d_sh: data structure (args and input)
 * Return: int
*/

int get_help(shell_d *d_sh)
{

	if (d_sh->tokens[1] == 0)
		aux_help_general();
	else if (_strcmp(d_sh->tokens[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(d_sh->tokens[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(d_sh->tokens[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(d_sh->tokens[1], "help") == 0)
		aux_help();
	else if (_strcmp(d_sh->tokens[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(d_sh->tokens[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(d_sh->tokens[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, d_sh->tokens[0],
		      _strlen(d_sh->tokens[0]));

	d_sh->status = 0;
	return (1);
}

/**
 * aux_help_env - Help information for the builtin env
 */

void aux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_setenv - Help information for the builtin setenv
 */

void aux_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 */

void aux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * aux_help_general - Entry point for help information for the help builtin
 */

void aux_help_general(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

#include "main.h"

/**
 * main - starts the simple shell programme
 * @ac: num of param (unused)
 * @av: arr of command list argument
 * Return: Always 0.
 */

int main(__attribute__((unused)) int ac, char **av)
{
	shell_d d_sh;

	signal(SIGINT, get_sigint);
	set_data(&d_sh, av);
	start_shell(&d_sh);
	free_data(&d_sh);

	if (d_sh.status < 0)
		return (255);

	return (d_sh.status);
}

/**
 * set_data - provides struct val
 * @d_sh: struct param
 * @av: list of arguments
 */

void set_data(shell_d *d_sh, char **av)
{
	unsigned int i;

	d_sh->av = av;
	d_sh->input = NULL;
	d_sh->tokens = NULL;
	d_sh->status = 0;
	d_sh->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	d_sh->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		d_sh->_environ[i] = _strdup(environ[i]);
	}

	d_sh->_environ[i] = NULL;
	d_sh->pid = aux_itoa(getpid());
}

/**
 * start_shell - this starts the shell to recieve commands
 * @d_sh: data relevant (av, input, args)
 */

void start_shell(shell_d *d_sh)
{
	int j, i_eof;
	char *input;

	j = 1;
	while (j == 1)
	{
		write(STDIN_FILENO, "Turf-$ ", 7);
		input = get_line(&i_eof);
		if (i_eof != -1)
		{
			input = rm_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(d_sh, input) == 1)
			{
				d_sh->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, d_sh);
			j = split_commands(d_sh, input);
			d_sh->counter += 1;
			free(input);
		}
		else
		{
			j = 0;
			free(input);
		}
	}
}

/**
 * rm_comment - removes comments from the input
 * @input: input string
 * Return: pointer to input without comments
 */

char *rm_comment(char *input)
{
	int i, n;

	n = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				n = i;
		}
	}

	if (n != 0)
	{
		input = _realloc(input, i, n + 1);
		input[n] = '\0';
	}

	return (input);
}

/**
 * free_data - frees memory alloc for struct
 * @d_sh: param
 */

void free_data(shell_d *d_sh)
{
	unsigned int i;

	for (i = 0; d_sh->_environ[i]; i++)
	{
		free(d_sh->_environ[i]);
	}

	free(d_sh->_environ);
	free(d_sh->pid);
}

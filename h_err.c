#include "main.h"

/**
 * get_err - calls the error according the builtin, syntax or permission
 * @d_sh: data structure that contains arguments
 * @eval: error value
 * Return: error
 */

int get_err(shell_d *d_sh, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = env_err(d_sh);
		break;
	case 126:
		err = path_126_err(d_sh);
		break;
	case 127:
		err = error404(d_sh);
		break;
	case 2:
		if (_strcmp("exit", d_sh->tokens[0]) == 0)
			err = exit_error(d_sh);
		else if (_strcmp("cd", d_sh->tokens[0]) == 0)
			err = get_cd_err(d_sh);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	d_sh->status = eval;
	return (eval);
}

/**
 * strcat_cd - function that concatenates the message for cd error
 * @d_sh: data relevant (directory)
 * @msg: message to print
 * @err: output message
 * @ver_str: counter lines
 * Return: error message
 */

char *strcat_cd(shell_d *d_sh, char *msg, char *err, char *ver_str)
{
	char *illegal_flag;

	_strcpy(err, d_sh->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, d_sh->tokens[0]);
	_strcat(err, msg);
	if (d_sh->tokens[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = d_sh->tokens[1][1];
		illegal_flag[2] = '\0';
		_strcat(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(err, d_sh->tokens[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * get_cd_err - error message for cd command in get_cd
 * @d_sh: data relevant (directory)
 * Return: Error message
 */
char *get_cd_err(shell_d *d_sh)
{
	int len, len_id;
	char *err, *ver_str, *msg;

	ver_str = aux_itoa(d_sh->counter);
	if (d_sh->tokens[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(d_sh->tokens[1]);
	}

	len = _strlen(d_sh->av[0]) + _strlen(d_sh->tokens[0]);
	len += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = strcat_cd(d_sh, msg, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * error404 - generic error message for command not found
 * @d_sh: data relevant (counter, arguments)
 * Return: Error message
 */

char *error404(shell_d *d_sh)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(d_sh->counter);
	len = _strlen(d_sh->av[0]) + _strlen(ver_str);
	len += _strlen(d_sh->tokens[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}

	_strcpy(err, d_sh->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, d_sh->tokens[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(ver_str);

	return (err);
}

/**
 * exit_error - generic error message for exit in get_exit
 * @d_sh: data relevant (counter, arguments)
 * Return: Error message
 */
char *exit_error(shell_d *d_sh)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(d_sh->counter);
	len = _strlen(d_sh->av[0]) + _strlen(ver_str);
	len += _strlen(d_sh->tokens[0]) + _strlen(d_sh->tokens[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, d_sh->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, d_sh->tokens[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, d_sh->tokens[1]);
	_strcat(err, "\n\0");
	free(ver_str);

	return (err);
}

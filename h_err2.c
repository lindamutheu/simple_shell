#include "main.h"

/**
 * env_err - error message for env in get_env.
 * @d_sh: data relevant (counter, arguments)
 * Return: error message.
 */

char *env_err(shell_d *d_sh)
{
	int len;
	char *err, *ver_str, *msg;

	ver_str = aux_itoa(d_sh->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(d_sh->av[0]) + _strlen(ver_str);
	len += _strlen(d_sh->tokens[0]) + _strlen(msg) + 4;
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
	_strcat(err, msg);
	_strcat(err, "\0");
	free(ver_str);

	return (err);
}
/**
 * path_126_err - error message for path and failure denied permission.
 * @d_sh: data relevant (counter, arguments).
 * Return: The error string.
 */

char *path_126_err(shell_d *d_sh)
{
	int len;
	char *ver_str, *err;

	ver_str = aux_itoa(d_sh->counter);
	len = _strlen(d_sh->av[0]) + _strlen(ver_str);
	len += _strlen(d_sh->tokens[0]) + 24;
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
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}

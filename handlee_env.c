#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 * @d_sh: data relevant.
 * Return: 1 on success.
 */

int _env(shell_d *d_sh)
{
	int i, j;

	for (i = 0; d_sh->_environ[i]; i++)
	{

		for (j = 0; d_sh->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, d_sh->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	d_sh->status = 0;

	return (1);
}
/**
 * set_env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @d_sh: data structure (environ)
 */

void set_env(char *name, char *value, shell_d *d_sh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; d_sh->_environ[i]; i++)
	{
		var_env = _strdup(d_sh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(d_sh->_environ[i]);
			d_sh->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	d_sh->_environ = _reallocdp(d_sh->_environ, i, sizeof(char *) * (i + 2));
	d_sh->_environ[i] = copy_info(name, value);
	d_sh->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @d_sh: data relevant (env name and env value)
 * Return: 1 on success.
 */

int _setenv(shell_d *d_sh)
{

	if (d_sh->tokens[1] == NULL || d_sh->tokens[2] == NULL)
	{
		get_err(d_sh, -1);
		return (1);
	}

	set_env(d_sh->tokens[1], d_sh->tokens[2], d_sh);

	return (1);
}

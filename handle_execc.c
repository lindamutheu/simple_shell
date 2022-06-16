#include "main.h"

/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */

int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */

char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 * @d_sh: data structure
 * Return: 0 if is not an executable, other number if it does
 */

int is_executable(shell_d *d_sh)
{
	struct stat st;
	int i;
	char *input;

	input = d_sh->tokens[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_err(d_sh, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 * @dir: destination directory
 * @d_sh: data structure
 * Return: 1 if there is an error, 0 if not
 */

int check_error_cmd(char *dir, shell_d *d_sh)
{
	if (dir == NULL)
	{
		get_err(d_sh, 127);
		return (1);
	}

	if (_strcmp(d_sh->tokens[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_err(d_sh, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(d_sh->tokens[0], X_OK) == -1)
		{
			get_err(d_sh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 * @d_sh: data relevant (args and input)
 * Return: 1 on success.
 */

int cmd_exec(shell_d *d_sh)
{
	pid_t pd;
	pid_t wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = is_executable(d_sh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(d_sh->tokens[0], d_sh->_environ);
		if (check_error_cmd(dir, d_sh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(d_sh->tokens[0], d_sh->_environ);
		else
			dir = d_sh->tokens[0];
		execve(dir + exec, d_sh->tokens, d_sh->_environ);
	}
	else if (pd < 0)
	{
		perror(d_sh->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	d_sh->status = state / 256;
	return (1);
}

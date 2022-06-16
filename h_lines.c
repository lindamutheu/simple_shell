#include "main.h"

/**
 * get_line - reads the input string.
 * @i_eof: param
 * Return: value of getline function
 */

char *get_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

/**
 * read_line - Read input from line stream
 * @cmd_line: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */

ssize_t read_line(char **cmd_line, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	assignto_line(cmd_line, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}


/**
 * assignto_line - assigns the line var for get_line
 * @cmd_line: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */

void assignto_line(char **cmd_line, size_t *n, char *buffer, size_t j)
{

	if (*cmd_line == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*cmd_line = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*cmd_line = buffer;
	}
	else
	{
		_strcpy(*cmd_line, buffer);
		free(buffer);
	}
}


/**
 * exec_line - finds builtins and commands
 * @d_sh: data relevant (args)
 * Return: 1 on success.
 */

int exec_line(shell_d *d_sh)
{
	int (*builtin)(shell_d *d_sh);

	if (d_sh->tokens[0] == NULL)
		return (1);

	builtin = get_builtin(d_sh->tokens[0]);

	if (builtin != NULL)
		return (builtin(d_sh));

	return (cmd_exec(d_sh));
}

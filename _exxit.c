#include "main.h"

/**
 * exit_shell - exits the shell
 * @d_sh: data relevant (status and args)
 * Return: 0 on success.
 */

int exit_shell(shell_d *d_sh)
{
	unsigned int ustatuss;
	int is_digitt;
	int str_lenn;
	int big_nnumber;

	if (d_sh->tokens[1] != NULL)
	{
		ustatuss = _atoi(d_sh->tokens[1]);
		is_digitt = _isdigit(d_sh->tokens[1]);
		str_lenn = _strlen(d_sh->tokens[1]);
		big_nnumber = ustatuss > (unsigned int)INT_MAX;
		if (!is_digitt || str_lenn > 10 || big_nnumber)
		{
			get_err(d_sh, 2);
			d_sh->status = 2;
			return (1);
		}
		d_sh->status = (ustatuss % 256);
	}
	return (0);
}

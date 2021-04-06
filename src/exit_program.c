/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/06 17:21:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "libft.h"
#include "proto.h"

void	reset_term(void)
{
	t_data	*data;

	data = getdata();
	if (!data->term.changed)
		return ;
	ft_putstr_fd("Resetting terminal\n", STDOUT_FILENO);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->term.original) == -1)
		ft_perror("tcsetattr");
}

void	exit_program(t_errnum errnum, char *err_str)
{
	int	status;

	if (errnum != success)
	{
		ft_perror(err_str);
		status = EXIT_FAILURE;
	}
	reset_term();
	exit(status);
}

void	exit_perror(int exit_status, char *str)
{
	ft_perror(str);
	reset_term();
	exit(exit_status);
}

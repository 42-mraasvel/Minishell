/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:45:47 by mraasvel      ########   odam.nl         */
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
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->term.original) == -1)
		ft_perror("tcsetattr");
}

void	exit_program(t_errnum errnum, char *err_str)
{
	int	status;

	status = 0;
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

void	end_program(t_data *data)
{
	ft_free_split(data->envp);
	vect_free(data->exec_errors, NULL);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	reset_term();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

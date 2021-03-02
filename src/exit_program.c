/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/02 18:01:08 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"

void	ft_perror(t_errnum errnum, char *err_str)
{
	// do something with errnum?
	(void)errnum;
	ft_putstr(err_str);
}

void	exit_program(t_errnum errnum, char *err_str)
{
	if (errnum != success)
	{
		ft_perror(errnum, err_str);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

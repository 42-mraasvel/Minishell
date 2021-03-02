/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/01 09:25:59 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "proto.h"

void	exit_program(t_errnums errnum, char *err_str)
{
	if (errnum != success)
	{
		ft_perror(errnum, err_str);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

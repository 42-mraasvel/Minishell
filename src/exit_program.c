/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:49:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/22 11:10:57 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "libft.h"

void	exit_program(t_errnum errnum, char *err_str)
{
	if (errnum != success)
	{
		perror(err_str);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

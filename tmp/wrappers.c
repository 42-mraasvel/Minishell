/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/01 23:30:50 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

/*
** Checks malloc return value
** exits program if error
*/

void	*malloc_guard(void *malloc_return)
{
	if (malloc_return == NULL)
		exit_program(error, "Malloc Error");
	return (malloc_return);
}

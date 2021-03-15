/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 12:49:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/stat.h>
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

/*
** Return true if file exists
*/

int	file_exists(char *filename)
{
	struct stat	buf;
	int			ret;

	ret = stat(filename, &buf);
	if (ret == 0)
		return (true);
	return (false);
}

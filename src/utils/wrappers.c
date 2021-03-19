/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/19 09:19:00 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include "libft.h"
#include "proto.h"

void	ft_perror(char *str)
{
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	perror(str);
}

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

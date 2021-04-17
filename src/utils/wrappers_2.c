/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 14:34:48 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "proto.h"

t_bool	isdir(char *filename)
{
	struct stat	buf;
	int			ret;

	ret = stat(filename, &buf);
	if (ret == 0 && !S_ISREG(buf.st_mode))
		return (ft_true);
	return (ft_false);
}

/*
** Return true if file exists
*/

int	file_exists(char *filename)
{
	struct stat	buf;
	int			ret;

	ret = stat(filename, &buf);
	if (ret == 0 && S_ISREG(buf.st_mode))
		return (ft_true);
	return (ft_false);
}

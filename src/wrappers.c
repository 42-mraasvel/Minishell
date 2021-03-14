/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 23:43:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/stat.h>
#include "libft.h"
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

	return (stat(filename, &buf) == 0);
}

#ifdef __APPLE__

char	*get_path(void)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (environ[i]);
}

#else

char	*get_path(void)
{
	size_t	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		if (ft_strncmp(__environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (__environ[i]);
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 14:29:21 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/stat.h>
#include "header.h"
#include "libft.h"
#include "proto.h"

void	ft_perror(char *str)
{
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	perror(str);
}

void	ft_putprompt(char *prefix)
{
	if (prefix != NULL)
		ft_putstr_fd(prefix, STDOUT_FILENO);
	write(STDOUT_FILENO, MINISHELL_PROMPT, sizeof(MINISHELL_PROMPT));
}

/*
** Checks malloc return value
** exits program if error
*/

void	*malloc_guard(void *malloc_return)
{
	if (malloc_return == NULL)
	{
		perror("-bash: malloc");
		exit(EXIT_FAILURE);
	}
	return (malloc_return);
}

void	*ft_malloc(size_t size)
{
	return (malloc_guard(malloc(size)));
}

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

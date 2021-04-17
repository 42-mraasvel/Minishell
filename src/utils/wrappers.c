/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrappers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 23:27:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 14:36:00 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "header.h"
#include "libft.h"

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

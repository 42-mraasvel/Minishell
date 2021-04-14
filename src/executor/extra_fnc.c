/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra_fnc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 16:51:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:53:45 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include "structs.h"
#include "libft.h"

int	isbuiltin(char *arg)
{
	int					i;
	static const char	*builtins[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(builtins[i], arg) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	close_fds(t_node *node)
{
	if (node->fds[0] != -1)
		if (close(node->fds[0]) == -1)
			ft_perror("close");
	if (node->fds[1] != -1)
		if (close(node->fds[1]) == -1)
			ft_perror("close");
	node->fds[0] = -1;
	node->fds[1] = -1;
}

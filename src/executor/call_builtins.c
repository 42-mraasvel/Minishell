/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   call_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 08:42:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/19 08:40:22 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "executor.h"
#include "libft.h"
#include "proto.h"

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

static t_builtin	get_builtin(char *name)
{
	int						i;
	static const t_builtin	builtins[] = {
		ft_echo,
		NULL,
		ft_pwd,
		ft_export,
		ft_unset,
		ft_env,
		ft_exit
	};

	i = isbuiltin((name));
	if (i < 0 || i > 6)
		return (NULL);
	return (builtins[i]);
}

/*
** This should dup2 file descriptors
** Not fork the process though
*/

int	exec_builtin(t_node *node, t_data *data)
{
	t_builtin	fnct;
	int			fd_copy[2];

	fnct = get_builtin(node->args[0]);
	if (fnct == NULL)
		return (-1);
	set_fds_builtin(node, fd_copy); // We want to make a copy of the replaced fds as well

	reset_fds_builtin(); // So that we can reset them after executing the program
	return (data->exit_status);
}

/*
** Array of pointers would be nice I guess
*/

int	call_builtins(t_data *data, t_node *node)
{
	if (execve(node->args[0], node->args, data->envp) == -1)
	{
		perror("-bash");
		exit_program(syscall_error, "Execve Error in child process");
	}
	return (0);
}

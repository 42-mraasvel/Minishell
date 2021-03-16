/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   call_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 08:42:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 13:39:43 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "libft.h"
#include "proto.h"

/*
** Array of pointers would be nice I guess
*/

int	call_builtins(t_data *data, t_node *node)
{
	static	int	(*builtins[])(t_data*) = {
		ft_env
	};

	if (ft_strstr(node->args[0], "env") != NULL)
		exit(ft_env(data));
	else if (execve(node->args[0], node->args, data->envp) == -1)
		exit_program(syscall_error, "Execve Error in child process");
	return (0);
}

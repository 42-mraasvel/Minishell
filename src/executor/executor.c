/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:12:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 12:52:01 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "proto.h"
#include "header.h"
#include "structs.h"

int	exec_semicolon(t_node *node, t_data *data)
{
	(void)node;
	flush_error(data);
	if (data->error.errnum != success)
		return (-1);
	return (0);
}

static int	execute_node(t_node *node, t_data *data)
{
	static	int	(*executors[])(t_node *, t_data *) = {
		exec_command,
		exec_pipe,
		exec_semicolon
	};

	if (executors[node->rule](node, data) == -1)
		return (-1);
	return (0);
}

int	executor(t_node *root, t_data *data)
{
	if (apply_prefix_tree_data(root, data, execute_node) == -1)
		return (-1);
	return (0);
}

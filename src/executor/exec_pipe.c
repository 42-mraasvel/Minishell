/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:27:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/23 17:29:40 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "structs.h"
#include "structs.h"
#include "proto.h"

static t_node	*next_command(t_node *node)
{
	if (node->rule == t_pipe)
		return (node->left);
	else
		return (next_command(node->right));
}

static int	set_write_end(t_node *node, int fd)
{
	if (node->fds[1] == -1)
		node->fds[1] = fd;
	else if (close(fd) == -1)
		return (-1);
	return (0);
}

static int	set_read_end(t_node *node, int fd)
{
	if (node->fds[0] == -1)
		node->fds[0] = fd;
	else if (close(fd) == -1)
		return (-1);
	return (0);
}

static int	start_children(t_node *node, t_data *data)
{
	int	tmp;
	int	total_pid;

	total_pid = execute_node(node->left, data);
	if (total_pid == -1)
		return (-1);
	tmp = execute_node(node->right, data);
	if (tmp == -1)
		return (-1);
	total_pid += tmp;
	return (total_pid);
}

/*
** In this function:
** initialize pipe and out/in fds of left and right nodes respectively
** If the fd is already taken (by redirection for example)
** it's not changed and that end of the pipe is closed.
*/

int	exec_pipe(t_node *node, t_data *data)
{
	int		fds[2];
	t_node	*right_cmd;

	if (node->left == NULL || node->right == NULL)
		return (-1);
	if (pipe(fds) == -1)
		return (set_err_data_int(data, syscall_error, -1));
	right_cmd = node->right;
	if (right_cmd->rule == t_pipe)
		right_cmd = next_command(node->right);
	if (set_read_end(right_cmd, fds[0]) == -1)
		return (set_err_data_int(data, syscall_error, -1));
	if (set_write_end(node->left, fds[1]) == -1)
		return (set_err_data_int(data, syscall_error, -1));
	return (start_children(node, data));
}

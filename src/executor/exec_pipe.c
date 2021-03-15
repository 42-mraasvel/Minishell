/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:27:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 20:23:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "header.h"
#include "tree.h"
#include "proto.h"

static t_node	*next_command(t_node *node)
{
	if (node->rule == t_pipe)
		return (node->left);
	else
		return (next_command(node->right));
}

static void	set_write_end(t_node *node, int fd)
{
	if (node->fds[1] == -1)
		node->fds[1] = fd;
	else
		close(fd);
}

static void	set_read_end(t_node *node, int fd)
{
	if (node->fds[0] == -1)
		node->fds[0] = fd;
	else
		close(fd);
}

/*
** In this function:
** initialize pipe and out/in fds of left and right nodes respectively
** If the fd is already taken (by redirection for example)
** it's not changed and that end of the pipe is closed.
*/

void	exec_pipe(t_node *node)
{
	int		fds[2];
	t_node	*right_cmd;

	if (node->left == NULL || node->right == NULL)
		return ;
	if (pipe(fds) == -1)
		exit_program(error, "Pipe Fail");
	right_cmd = node->right;
	if (right_cmd->rule == t_pipe)
		right_cmd = next_command(node->right);
	set_read_end(right_cmd, fds[0]);
	set_write_end(node->left, fds[1]);
}

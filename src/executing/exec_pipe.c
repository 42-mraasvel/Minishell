/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:27:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:11:03 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "header.h"
#include "tree.h"
#include "proto.h"

t_node	*next_command(t_node *node)
{
	if (node->rule == t_pipe)
		return (node->left);
	else
		return (next_command(node->right));
}

/*
** In this function:
** initialize pipe and out/in fds of left and right nodes respectively
*/

void	exec_pipe(t_node *node)
{
	int		fds[2];
	t_node	*right_cmd;

	printf("Executing Pipe\n");
	if (node->left == NULL || node->right == NULL)
		return ;
	if (pipe(fds) == -1)
		exit_program(error, "Pipe Fail");
	if (node->left->fds[1] == -1)
		node->left->fds[1] = fds[1];
	else
		close(fds[0]);
	right_cmd = node->right;
	if (right_cmd->rule == t_pipe)
		right_cmd = next_command(node->right);
	if (right_cmd->fds[0] == -1)
		right_cmd->fds[0] = fds[0];
	else
		close(fds[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:12:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 17:44:26 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <unistd.h>
#include <sys/wait.h>
#include "proto.h"
#include "header.h"
#include "structs.h"

int	execute_node(t_node *node, t_data *data)
{
	static	int	(*executors[])(t_node *, t_data *) = {
		exec_command,
		exec_pipe,
		exec_semicolon
	};

	if (node == NULL)
		return (0);
	return (executors[node->rule](node, data));
}

/*
** Maybe we want to wait for each semicolon sequence?
*/

int	exec_semicolon(t_node *node, t_data *data)
{
	int	pid_total;

	pid_total = 0;
	if (node->left != NULL)
		pid_total += execute_node(node->left, data);
	flush_error(data);
	if (node->right != NULL)
		pid_total += execute_node(node->right, data);
	return (pid_total);
}

/*
** Idea:
**	Return total forks.
**	Wait for each fork, take the last fork's exit status (?)
**
** (Better) Alternative:
**	Return a vector of PIDs in [data]
**	Each time a fork is called: the PID is returned to the caller.
**	Wait for each pid using waitpid, guaranteeing the last fork's exit status.
*/

int	executor(t_node *root, t_data *data)
{
	int	pid_total;
	int	status;

	restore_term(data);
	pid_total = execute_node(root, data);
	if (pid_total == -1)
		return (-1);
	data->status = waiting;
	while (pid_total > 0)
	{
		int pid = wait(&status);
		pid_total--;
	}
	data->status = done;
	ft_setterm(data, 1);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
		data->exit_status = GENERAL_ERROR;
	return (0);
}

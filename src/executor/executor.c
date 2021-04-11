/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:12:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 19:05:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"
#include "proto.h"
#include "header.h"
#include "structs.h"
#include "libft.h"

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

static void	handle_status(t_data *data, int status)
{
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = WTERMSIG(status) + FATAL_ERROR_SIG;
		if (data->exit_status == 130)
		{
			data->interrupted = ft_true;
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		else if (data->exit_status == 131)
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
}

void	flush_waits(t_data *data)
{
	t_process	*process;
	size_t		i;
	int			status;

	if (data->processes == NULL)
		return ;
	process = (t_process *)(data->processes->table);
	i = 0;
	while (i < data->processes->nmemb)
	{
		if (process[i].ptype == builtin)
			data->exit_status = process[i].exit_status;
		else
		{
			waitpid(process[i].pid, &status, 0);
			handle_status(data, status);
			if (data->interrupted == ft_true)
			{
				kill_processes(data, i);
				break ;
			}
		}
		i++;
	}
	reset_processes(data);
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
	flush_waits(data);
	if (data->interrupted == ft_true)
		return (-1);
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
	int	ret;

	restore_term(data);
	ret = execute_node(root, data);
	if (ret == -1 || data->interrupted == ft_true)
		return (-1);
	flush_waits(data);
	flush_error(data);
	return (0);
}

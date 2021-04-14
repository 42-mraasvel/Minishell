/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   call_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 08:42:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:52:33 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "executor.h"
#include "libft.h"
#include "proto.h"

static t_builtin	get_builtin(char *name)
{
	int						i;
	static const t_builtin	builtins[] = {
		ft_echo,
		ft_cd,
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
** What are the errors?
** How do we handle these errors?
** Print an error message and continue?
** Or exit the program (probably not this one)
**
**	1. Save replaces FDs
**	2. Replace STD FDs
**	3. Close the one in node because they're unused
*/

static int	set_fds_builtin(t_node *node, int fds[2])
{
	if (node->fds[0] != -1)
	{
		fds[0] = dup(STDIN_FILENO);
		if (fds[0] == -1)
			exit_perror(GENERAL_ERROR, "dup");
		if (dup2(node->fds[0], STDIN_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		close(node->fds[0]);
		node->fds[0] = -1;
	}
	if (node->fds[1] != -1)
	{
		fds[1] = dup(STDOUT_FILENO);
		if (fds[1] == -1)
			exit_perror(GENERAL_ERROR, "dup");
		if (dup2(node->fds[1], STDOUT_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		close(node->fds[1]);
		node->fds[1] = -1;
	}
	return (success);
}

static int	reset_fds_builtin(int fds[2])
{
	if (fds[0] != -1)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		close(fds[1]);
	}
	return (success);
}

/*
** Fork builtin if part of pipe sequence
** Echo is already forked by default
*/

int	builtin_checkpipe(t_node *node, t_data *data)
{
	int	pid;

	if (data->executor_status != t_pipe
		|| ft_strcmp(node->args[0], "echo") == 0)
		return (0);
	pid = fork();
	if (pid == -1)
		exit_perror(GENERAL_ERROR, "fork");
	if (pid == 0)
	{
		close_all_fds(node, data->root);
		return (0);
	}
	close_fds(node);
	new_process(data, p_command, pid);
	return (1);
}

/*
** Doesn't fork the process and calls builtin functions
** Unless the process is part of a pipe, then it is forked
*/

int	exec_builtin(t_node *node, t_data *data)
{
	t_builtin	fnct;
	int			fd_copy[2];
	int			status;
	int			pid;

	pid = builtin_checkpipe(node, data);
	if (pid != 0)
		return (pid);
	fd_copy[0] = -1;
	fd_copy[1] = -1;
	fnct = get_builtin(node->args[0]);
	if (fnct == NULL)
		return (-1);
	if (cmd_redirects(node) == -1)
		return (0);
	set_fds_builtin(node, fd_copy);
	status = fnct(data, node->args);
	reset_fds_builtin(fd_copy);
	if (ft_strcmp(node->args[0], "echo") == 0)
		return (status);
	if (data->executor_status == t_pipe)
		exit(status);
	new_process(data, builtin, status);
	return (0);
}

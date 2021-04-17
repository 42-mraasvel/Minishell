/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 08:39:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 15:15:54 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include "header.h"
#include "libft.h"
#include "executor.h"
#include "expander.h"
#include "structs.h"
#include "proto.h"

static int	cmd_findpath(t_node *node, t_data *data)
{
	node->exec_path = NULL;
	if (ft_strcmp(node->args[0], "echo") == 0 || node->args[0][0] == '\0')
		node->exec_path = malloc_guard(ft_strdup(node->args[0]));
	else if (ft_strchr(node->args[0], '/') != NULL)
		node->exec_path = malloc_guard(ft_strdup(node->args[0]));
	else
		search_path(data, &node->exec_path, node->args[0]);
	return (0);
}

static void	set_redirection(t_node *node)
{
	if (node->fds[0] != -1)
	{
		if (dup2(node->fds[0], STDIN_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		if (close(node->fds[0]) == -1)
			ft_perror("close");
		node->fds[0] = -1;
	}
	if (node->fds[1] != -1)
	{
		if (dup2(node->fds[1], STDOUT_FILENO) == -1)
			exit_perror(GENERAL_ERROR, "dup2");
		if (close(node->fds[1]) == -1)
			ft_perror("close");
		node->fds[1] = -1;
	}
}

static int	finalize_cmd(t_node *node, t_data *data)
{
	int			pid;

	pid = fork();
	if (pid < 0)
	{
		ft_perror("fork");
		close_fds(node);
		return (-1);
	}
	if (pid == 0)
	{
		if (cmd_redirects(node) == -1)
			exit(GENERAL_ERROR);
		set_redirection(node);
		close_all_fds(node, data->root);
		if (ft_strcmp(node->args[0], "echo") == 0)
			exit(exec_builtin(node, data));
		if (execve(node->exec_path, node->args, data->envp) == -1)
			exit_perror(CANNOT_EXEC, node->exec_path);
	}
	new_process(data, p_command, pid);
	close_fds(node);
	return (1);
}

static int	check_redirections(t_node *node, t_data *data)
{
	if (cmd_redirects(node) == -1)
	{
		new_process(data, p_error, GENERAL_ERROR);
		return (0);
	}
	new_process(data, builtin, 0);
	close_fds(node);
	return (0);
}

int	exec_command(t_node *node, t_data *data)
{
	if (expand_node(node) == -1)
		return (0);
	if (node->args[0] == NULL)
		return (check_redirections(node, data));
	if (isbuiltin(node->args[0]) != -1 && ft_strcmp(node->args[0], "echo") != 0)
		return (exec_builtin(node, data));
	cmd_findpath(node, data);
	if (ft_strcmp(node->args[0], "echo") != 0
		&& ((!ft_strchr(node->exec_path, '/') && getenv("PATH"))
			|| !file_exists(node->exec_path)))
	{
		close_fds(node);
		new_process(data, p_error, CMD_NOT_FOUND);
		set_error_vec(data, cmd_not_found, node->exec_path, 0);
		flush_error(data);
		return (0);
	}
	return (finalize_cmd(node, data));
}

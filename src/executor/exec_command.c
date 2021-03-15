/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 13:10:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header.h"
#include "proto.h"
#include "libft.h"
#include "structs.h"

static int	close_fds(t_node *node)
{
	if (node->fds[0] != -1)
		if (close(node->fds[0]) == -1)
			return (-1);
	if (node->fds[1] != -1)
		return (close(node->fds[1]));
	return (0);
}

static int	set_fds(t_node *node)
{
	if (node->fds[0] != -1)
	{
		if (dup2(node->fds[0], STDIN_FILENO) == -1)
			return (-1);
		if (close(node->fds[0]) == -1)
			return (-1);
	}
	if (node->fds[1] != -1)
	{
		if (dup2(node->fds[1], STDOUT_FILENO) == -1)
			return (-1);
		if (close(node->fds[1]) == -1)
			return (-1);
	}
	return (0);
}

/*
** 1. Find if command exists in any specified PATH
** 2. Expand all arguments in the ARGS string
** 3. Fork Process
** 4. Replace stdin/stdout file descriptors
** 5. execute command with arguments
** 6. Wait until command is finished and check exit status (for error etc)
**
** ERRORS ARE NOT HANDLED YET
*/

void	print_command(t_node *node)
{
	int	i;

	i = 0;
	while (node->args[i] != NULL)
	{
		if (i != 0)
			printf(" ");
		printf("%s", node->args[i]);
		i++;
	}
	printf("\n");
	printf("\tFD[0][1] : %d | %d\n", node->fds[0], node->fds[1]);
}

static int	find_exec(char	**args, t_data *data)
{
	char	*original;
	int		ret;

	ret = 0;
	if (ft_strchr(args[0], '/') != NULL)
		return (0);
	original = ft_strdup(args[0]);
	if (original == NULL)
		return (set_err_data_int(data, malloc_error, -1));
	if (lookup_path(data, args, original) == -1)
		ret = -1;
	if (args[0] != original)
		free(original);
	return (ret);
}

int	exec_command(t_node *node, t_data *data)
{
	int	pid;

	printf("Executing Command:");
	print_command(node);

	find_exec(node->args, data);
	if (data->error.errnum != success)
		return (-1);
	if (!file_exists(node->args[0]))
		return (set_error_vec(data, cmd_not_found, node->args[0], 0));
	// We have to check if the command is a directory or not.
	pid = fork();
	if (pid < 0)
		return (set_err_data_int(data, syscall_error, -1));
	if (pid == 0)
	{
		if (set_fds(node) == -1)
			return (set_err_data_int(data, syscall_error, -1));
		//! Here we will our own functions if needed
		if (execve(node->args[0], node->args, data->envp) == -1)
			exit_program(syscall_error, "Execve Error in child process");
	}
	if (close_fds(node) == -1)
		return (set_err_data_int(data, syscall_error, -1));

	waitpid(pid, NULL, 0); // This should be used to get and set the exit status of the child process,
	// also options for additional instructions like waiting only for child to exit
	return (0);
}

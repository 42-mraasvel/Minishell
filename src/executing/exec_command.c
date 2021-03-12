/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 13:14:19 by mraasvel      ########   odam.nl         */
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
#include "tree.h"

void	close_fds(t_nodex *node)
{
	if (node->fds[0] != -1)
		close(node->fds[0]);
	if (node->fds[1] != -1)
		close(node->fds[1]);
}

void	set_fds(t_nodex *node)
{
	if (node->fds[0] != -1)
		dup2(node->fds[0], STDIN_FILENO);
	if (node->fds[1] != -1)
		dup2(node->fds[1], STDOUT_FILENO);
}

char	*get_cmd_path(char *cmd, char *path)
{
	size_t	len1;
	size_t	len;
	char	*path_string;

	len1 = ft_strlen(path);
	len = len1 + ft_strlen(cmd) + 2;
	path_string = (char *)malloc_guard(ft_calloc(len, sizeof(char)));
	ft_strlcpy(path_string, path, len);
	path_string[len1] = '/';
	ft_strlcat(path_string, cmd, len);
	return (path_string);
}

int	find_command(char **args, char *path)
{
	char	**paths;
	char	*str;
	size_t	i;
	int		ret;

	paths = (char **)malloc_guard(ft_split(path + 5, ':'));
	i = 0;
	ret = -1;
	while (paths[i] != NULL)
	{
		str = get_cmd_path(args[0], paths[i]);
		if (file_exists(str))
		{
			ret = 0;
			free(args[0]);
			args[0] = str;
			break ;
		}
		free(str);
		i++;
	}
	ft_free_split(paths);
	return (ret);
}

int	set_args(t_nodex *node)
{
	char	*path;

	path = get_path();
	if (path == NULL)
		return (-1);
	if (find_command(node->args, path) == -1)
		return (-1);
	return (success);
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

void	print_command(t_nodex *node)
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

#ifdef __APPLE__

void	exec_command(t_nodex *node)
{
	extern char	**environ;
	int	pid;

	if (set_args(node) == -1)
		exit_program(error, "Command not found");
	printf("Executing Command:");
	print_command(node);
	pid = fork();
	if (pid < 0)
		exit_program(error, "Fork Error");
	if (pid == 0)
	{
		set_fds(node);
		execve(node->args[0], node->args, environ);
	}
	close_fds(node);
	waitpid(pid, NULL, 0);
}

#else

void	exec_command(t_nodex *node)
{
	int	pid;

	if (set_args(node) == -1)
		exit_program(error, "Command not found");
	printf("Executing Command:");
	print_command(node);
	pid = fork();
	if (pid < 0)
		exit_program(error, "Fork Error");
	if (pid == 0)
	{
		set_fds(node);
		execve(node->args[0], node->args, __environ);
	}
	close_fds(node);
	waitpid(pid, NULL, 0);
}

#endif

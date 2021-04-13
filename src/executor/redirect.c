/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/26 10:14:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:46:58 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "executor.h"
#include "libft.h"
#include "proto.h"
#include "structs.h"

static int	dir_error(char *str)
{
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	return (-1);
}

static int	redir_append(t_node *node, char *pathname)
{
	if (isdir(pathname))
		return (dir_error(pathname));
	if (node->fds[1] != -1)
		close(node->fds[0]);
	node->fds[1] = open(pathname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (node->fds[1] == -1)
	{
		ft_perror(pathname);
		return (-1);
	}
	return (0);
}

static int	redir_out(t_node *node, char *pathname)
{
	if (isdir(pathname))
		return (dir_error(pathname));
	if (node->fds[1] != -1)
		close(node->fds[1]);
	node->fds[1] = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (node->fds[1] == -1)
	{
		ft_perror(pathname);
		return (-1);
	}
	return (0);
}

static int	redir_in(t_node *node, char *pathname)
{
	if (node->fds[0] != -1)
		close(node->fds[0]);
	node->fds[0] = open(pathname, O_RDONLY);
	if (node->fds[0] == -1)
	{
		ft_perror(pathname);
		return (-1);
	}
	return (0);
}

/*
** Return -1 if file doesn't exist
*/

int	cmd_redirects(t_node *node)
{
	static t_redirfct	redirs[] = {
		redir_in,
		redir_out,
		redir_append
	};
	size_t				i;
	t_token				token;

	i = 0;
	while (i < node->redirects->nmemb)
	{
		token = ((t_token *)node->redirects->table)[i];
		if (redirs[token.optype](node, token.start) == -1)
			return (-1);
		i++;
	}
	return (0);
}

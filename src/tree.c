/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:38 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/14 20:43:54 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "proto.h"
#include "tree.h"
#include "libft.h"
#include "libvect.h"

int	adjust_for_redirection(char ***args, int fds[2], int count)
{
	char	**adj;
	int		i;
	int		j;

	adj = malloc_guard(malloc((1 + count) * sizeof(char *)));
	if (adj == 0)
		return (0);
	i = 0;
	j = 0;
	while (*(*args + i))
	{
		if (!ft_strcmp(*(*args + i), "<"))
		{
			if (fds[0] != -1)
				if (close(fds[0]) == -1)
					return (0);
			free(*(*args + i));
			i++;
			if (*(*args + i))
			{
				fds[0] = open(*(*args + i), O_RDONLY);
				if (fds[0] == -1)
					return (0);
				free(*(*args + i));
			}
			else
				fds[0] = open("", O_RDONLY);
		}
		else if (!ft_strcmp(*(*args + i), ">"))
		{
			if (fds[1] != -1)
				if (close(fds[1]) == -1)
					return (0);
			free(*(*args + i));
			i++;
			if (*(*args + i))
			{
				fds[1] = open(*(*args + i), (O_WRONLY | O_CREAT), 0644);
				if (fds[1] == -1)
					return (0);
				free(*(*args + i));
			}
			else
				fds[1] = open("", (O_WRONLY | O_CREAT), 0644);
		}
		else if (!ft_strcmp(*(*args + i), ">>"))
		{
			if (fds[1] != -1)
				if (close(fds[1]) == -1)
					return (0);
			free(*(*args + i));
			i++;
			if (*(*args + i))
			{
				fds[1] = open(*(*args + i), (O_APPEND | O_CREAT), 0644);
				if (fds[1] == -1)
					return (0);
				free(*(*args + i));
			}
			else
				fds[1] = open("", (O_WRONLY | O_CREAT), 0644);
		}
		else if (ft_strcmp(*(*args + i), "<") && ft_strcmp(*(*args + i), ">") && ft_strcmp(*(*args + i), ">>"))
		{
			adj[j] = *(*args + i);
			j++;
		}
		if (*(*args + i))
			i++;
	}
	adj[j] = 0;
	free(*args);
	*args = adj;
	return (1);
}


t_node	*add_node(t_vect *tokens, size_t start, size_t end)
{
	t_node	*node;
	size_t	i;
	t_token	token;
	int		give_birth;
	int		count;

	if (start == end)
		return (NULL);
	node = (t_node*)malloc_guard(malloc(1 * sizeof(t_node)));
	if (node == 0)
		return (0);
	i = start;
	give_birth = 0;
	while (i < end && !give_birth)
	{
		if (*((t_token*)tokens->table)[i].start == ';')
		{
			give_birth = 1;
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i + 1, end);
			node->rule = semicolon;
		}
		i++;
	}
	i = start;
	while (i < end && !give_birth)
	{
		if (*((t_token*)tokens->table)[i].start == '|')
		{
			give_birth = 1;
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i + 1, end);
			node->rule = t_pipe;
		}
		i++;
	}
	if (!give_birth)
	{
		node->rule = command;
		node->left = 0;
		node->right = 0;
		node->fds[0] = -1;
		node->fds[1] = -1;
		i = start;
		node->args = malloc_guard(malloc((1 + (end - start)) * sizeof(char *)));
		if (node->args == 0)
			return (0);
		count = 0;
		while (i < end)
		{
			token = ((t_token*)tokens->table)[i];
			node->args[i - start] = ft_substr(token.start, 0, token.length);
			if (node->args[i - start] == 0)
				return (0);
			if ((token.type != operator && !(i - start)) || (token.type != operator && ((t_token*)tokens->table)[i - 1].type != operator))
				count++;
			i++;
		}
		node->args[i - start] = 0;
		if (count)
			if (adjust_for_redirection(&node->args, node->fds, count) == 0)
				return (0);
	}
	return (node);
}

t_node	*create_tree(t_vect *tokens)
{
	t_node	*tree;

	tree = add_node(tokens, 0, tokens->nmemb);
	return (tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:38 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/16 18:49:13 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "proto.h"
#include "structs.h"
#include "libft.h"
#include "libvect.h"

int	check_semicolon(t_vect *tokens, size_t start, size_t end, t_node *node)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (((t_token*)tokens->table)[i].optype == o_semicolon)
		{
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i + 1, end);
			node->rule = semicolon;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_pipe(t_vect *tokens, size_t start, size_t end, t_node *node)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (((t_token*)tokens->table)[i].optype == o_pipe)
		{
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i + 1, end);
			node->rule = t_pipe;
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_args(t_vect *tokens, size_t start, size_t end, char ***args)
{
	t_token	token;
	int		count;
	size_t	i;

	count = 0;
	i = start;
	while (i < end)
	{
		token = ((t_token*)tokens->table)[i];
		if (token.type == word && (i == start
				|| ((t_token*)tokens->table)[i - 1].type == word))
			count++;
		i++;
	}
	*args = malloc_guard(malloc((1 + count) * sizeof(char *)));
	if (*args == 0)
		return (0);
	return (1);
}

int	parse_redirect_in(t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[0] != -1)
		if (close(node->fds[0]) == -1)
			return (0);
	(*index)++;
	node->fds[0] = open(filename->start, O_RDONLY);
	if (node->fds[0] == -1)
		return (0);
	free(filename->start);
	return (1);
}

int	parse_redirect_out(t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[1] != -1)
		if (close(node->fds[1]) == -1)
			return (0);
	(*index)++;
	node->fds[1] = open(filename->start, (O_WRONLY | O_APPEND | O_CREAT), 0644);
	if (node->fds[1] == -1)
		return (0);
	free(filename->start);
	return (1);
}

int	parse_redirect_append(t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[1] != -1)
		if (close(node->fds[1]) == -1)
			return (0);
	(*index)++;
	node->fds[1] = open(filename->start, (O_WRONLY | O_CREAT), 0644);
	if (node->fds[1] == -1)
		return (0);
	free(filename->start);
	return (1);
}

int	check_for_redirect(t_token *curr, t_token *next, t_node *node,
	size_t *index)
{
	if (curr->optype == redirect_in)
	{
		if (!parse_redirect_in(next, node, index))
			return (0);
	}
	else if (curr->optype == redirect_out)
	{
		if (!parse_redirect_out(next, node, index))
			return (0);
	}
	else if (curr->optype == redirect_append)
	{
		if (!parse_redirect_append(next, node, index))
			return (0);
	}
	return (1);
}

int	get_args(t_vect *tokens, size_t start, size_t end, t_node *node)
{
	t_token	token;
	size_t	i;
	int		j;

	if (create_args(tokens, start, end, &node->args) == 0)
		return (0);
	i = start;
	j = 0;
	while (i < end)
	{
		token = ((t_token*)tokens->table)[i];
		if (token.type == word)
		{
			node->args[j] = token.start;
			j++;
		}
		else if (token.type == operator)
			if (!check_for_redirect(&token, &((t_token*)tokens->table)[i + 1],
					node, &i))
				return (0);
		i++;
	}
	node->args[j] = 0;
	return (1);
}

t_node	*add_node(t_vect *tokens, size_t start, size_t end)
{
	t_node	*node;
	t_token	token;

	if (start == end)
		return (NULL);
	node = (t_node*)malloc_guard(malloc(1 * sizeof(t_node)));
	if (node == 0)
		return (0);
	if (!check_semicolon(tokens, start, end, node)
		|| !check_pipe(tokens, start, end, node))
	{
		node->rule = command;
		node->left = 0;
		node->right = 0;
		node->fds[0] = -1;
		node->fds[1] = -1;
		if (get_args(tokens, start, end, node) == 0)
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

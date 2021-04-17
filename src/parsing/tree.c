/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:38 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/17 15:10:09 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "proto.h"
#include "structs.h"
#include "libvect.h"

static int	create_args(t_vect *tokens, size_t start, size_t end, char ***args)
{
	t_token	token;
	int		count;
	size_t	i;

	count = 0;
	i = start;
	while (i < end)
	{
		token = ((t_token *)tokens->table)[i];
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

static int	get_args(t_vect *tokens, size_t start, size_t end, t_node *node)
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
		token = ((t_token *)tokens->table)[i];
		if (token.type == word)
		{
			node->args[j] = token.start;
			j++;
		}
		else if (token.type == operator)
			if (!check_for_redirect(&token, &((t_token *)tokens->table)[i + 1],
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

	if (start == end)
		return (NULL);
	node = (t_node *)malloc_guard(malloc(1 * sizeof(t_node)));
	if (node == 0)
		return (0);
	node->redirects = malloc_guard(vect_init(0, sizeof(t_token)));
	node->exec_path = 0;
	node->fds[0] = -1;
	node->fds[1] = -1;
	if (!check_semicolon(tokens, start, end, node)
		&& !check_pipe(tokens, start, end, node))
	{
		node->rule = command;
		node->left = 0;
		node->right = 0;
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

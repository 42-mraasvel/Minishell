/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_operator.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/17 15:00:28 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/17 15:09:12 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include "header.h"
#include "structs.h"

int	check_semicolon(t_vect *tokens, size_t start, size_t end, t_node *node)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		if (((t_token *)tokens->table)[i].optype == o_semicolon)
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
		if (((t_token *)tokens->table)[i].optype == o_pipe)
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

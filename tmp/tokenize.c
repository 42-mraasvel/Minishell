/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:08:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/02 15:31:06 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

void	traverse(t_node *tree)
{
	if (tree == NULL)
		return ;
	traverse(tree->left);
	//! use current node
	traverse(tree->right);
}

/*
** These functions return the length of the token.
*/

size_t	tokenize_operator(char *start)
{
	return (0);
}

size_t	tokenize_word(char *start)
{
	return (0);
}

size_t	tokenize_squote(char *start)
{
	return (0);
}

size_t	tokenize_dquote(char *start)
{
	return (0);
}

size_t	tokenize_variable(char *start)
{
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 08:42:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 14:14:41 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include "lexer.h"

void	tree_free(t_node *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		tree_free(root->left);
	if (root->right != NULL)
		tree_free(root->right);
	// if (root->rule == command)
	// 	free(root->args);
	if (root->rule == command)
		ft_free_split(root->args);
	if (root->rule == command && root->fds[0] != -1)
		close(root->fds[0]);
	if (root->rule == command && root->fds[1] != -1)
		close(root->fds[1]);
	free(root);
}

/*
** If (*fct) returns -1 it will stop the traversal and return error
** Error code should be set in fct according to t_errnums.
** Applies mid left right, EXCEPT for semicolons
*/

int	apply_prefix_tree_data(
		t_node *root, t_data *data, int (*fct)(t_node *, t_data *))
{
	if (root == NULL || fct == NULL)
		return (-1);
	if (root->rule != semicolon)
		if (fct(root, data) == -1)
			return (-1);
	if (root->left != NULL)
		if (apply_prefix_tree_data(root->left, data, fct) == -1)
			return (-1);
	if (root->rule == semicolon)
		if (fct(root, data) == -1)
			return (-1);
	if (root->right != NULL)
		if (apply_prefix_tree_data(root->right, data, fct) == -1)
			return (-1);
	return (0);
}

void	apply_prefix_tree(t_node *root, void (*fct)(t_node *))
{
	if (root == NULL || fct == NULL)
		return ;
	fct(root);
	if (root->left != NULL)
		apply_prefix_tree(root->left, fct);
	if (root->right != NULL)
		apply_prefix_tree(root->right, fct);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 08:42:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:06:48 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "header.h"
#include "lexer.h"

t_nodex	*new_node(t_token data)
{
	t_nodex	*new;

	new = (t_nodex*)malloc_guard(malloc(1 * sizeof(t_nodex)));
	new->right = NULL;
	new->left = NULL;
	new->args = NULL;
	new->rule = nothing;
	new->fds[0] = -1;
	new->fds[1] = -1;
	new->token = data;
	return (new);
}

void	tree_free(t_nodex *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		tree_free(root->left);
	if (root->right != NULL)
		tree_free(root->right);
	// if (root->args != NULL)
	// 	ft_free_split(root->args);
	if (root->rule == command)
		ft_free_split(root->args);
	if (root->fds[0] != -1)
		close(root->fds[0]);
	if (root->fds[1] != -1)
		close(root->fds[1]);
	free(root);
}

void	apply_inorder_tree(t_nodex *root, void (*fct)(t_nodex *))
{
	if (root == NULL || fct == NULL)
		return ;
	fct(root);
	if (root->left != NULL)
		apply_inorder_tree(root->left, fct);
	if (root->right != NULL)
		apply_inorder_tree(root->right, fct);
}

// typedef enum e_rule
// {
// 	command,
// 	t_pipe,
// 	semicolon,
// 	nothing
// }	t_rule;

char	*get_rule(t_rule rule)
{
	static char	*rules[] = {
		"Command",
		"Pipe",
		"Semicolon"
	};

	return (rules[rule]);
}

void	print_tree_depth(t_nodex *root, int depth)
{
	print_node(root);
	printf("\tDepth: %d: Rule: %s\n", depth, get_rule(root->rule));
	if (root->left != NULL)
		print_tree_depth(root->left, depth + 1);
	if (root->right != NULL)
		print_tree_depth(root->right, depth + 1);
}

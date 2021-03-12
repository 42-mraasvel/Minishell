/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 08:42:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:59:56 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "header.h"
#include "lexer.h"

t_node	*new_node(t_token data)
{
	t_node	*new;

	(void)data;
	new = (t_node*)malloc_guard(malloc(1 * sizeof(t_node)));
	new->right = NULL;
	new->left = NULL;
	new->args = NULL;
	new->fds[0] = -1;
	new->fds[1] = -1;
	return (new);
}

void	tree_free(t_node *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		tree_free(root->left);
	if (root->right != NULL)
		tree_free(root->right);
	if (root->rule == command)
		ft_free_split(root->args);
	if (root->fds[0] != -1)
		close(root->fds[0]);
	if (root->fds[1] != -1)
		close(root->fds[1]);
	free(root);
}

void	apply_inorder_tree(t_node *root, void (*fct)(t_node *))
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
		"Semicolon",
		"Nothing"
	};

	if (rule > 3)
		return (rules[3]);
	return (rules[rule]);
}

void	print_tree_depth(t_node *root, int depth)
{
	if (root == NULL) {
		printf("Root is NULL\n");
		return ;
	}
	print_node(root);
	printf("\tDepth: %d: Rule: %s\n", depth, get_rule(root->rule));
	if (root->left != NULL)
	{
		printf("\nLEFT:\n");
		print_tree_depth(root->left, depth + 1);
	}
	if (root->right != NULL)
	{
		printf("\nRIGHT:\n");
		print_tree_depth(root->right, depth + 1);
	}
	printf("Returning...\n");
}

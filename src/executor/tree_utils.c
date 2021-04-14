/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 08:42:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:55:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include "lexer.h"
#include "executor.h"

void	delete_redirect_token(void *token)
{
	free(((t_token *)token)->start);
}

void	tree_free(t_node *root)
{
	if (root == NULL)
		return ;
	if (root->left != NULL)
		tree_free(root->left);
	if (root->right != NULL)
		tree_free(root->right);
	if (root->rule == command && root->exec_path != NULL)
		free(root->exec_path);
	if (root->rule == command && root->args != NULL)
		ft_free_split(root->args);
	if (root->rule == command && root->fds[0] != -1)
		close(root->fds[0]);
	if (root->rule == command && root->fds[1] != -1)
		close(root->fds[1]);
	vect_free(root->redirects, delete_redirect_token);
	free(root);
}

void	close_all_fds(t_node *node, t_node *root)
{
	if (root == node || root == NULL)
		return ;
	close_fds(root);
	close_all_fds(node, root->left);
	close_all_fds(node, root->right);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_redirection.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/17 15:01:25 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/17 15:09:43 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "proto.h"
#include "header.h"
#include "structs.h"
#include "libvect.h"

static int	parse_redirect_in(t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[0] != -1)
		if (close(node->fds[0]) == -1)
			return (0);
	(*index)++;
	filename->optype = redirect_in;
	if (vect_pushback(node->redirects, filename) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (1);
}

static int	parse_redirect_out(t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[1] != -1)
		if (close(node->fds[1]) == -1)
			return (0);
	(*index)++;
	filename->optype = redirect_out;
	if (vect_pushback(node->redirects, filename) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (1);
}

static int	parse_redirect_append(
	t_token *filename, t_node *node, size_t *index)
{
	if (node->fds[1] != -1)
		if (close(node->fds[1]) == -1)
			return (0);
	(*index)++;
	filename->optype = redirect_append;
	if (vect_pushback(node->redirects, filename) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (1);
}

int	check_for_redirect(
	t_token *curr, t_token *next, t_node *node, size_t *index)
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

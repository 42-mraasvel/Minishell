/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_execute_tree.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:12:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:11:10 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "proto.h"
#include "header.h"
#include "tree.h"

void	exec_semicolon(t_node *node)
{
	printf("Executing Semicolon\n");
	(void)node;
}

void	execute_node(t_node *node)
{
	static	void	(*executors[])(t_node *node) = {
		exec_command,
		exec_pipe,
		exec_semicolon
	};

	executors[node->rule](node);
}

void	execute_tree(t_node *root)
{
	apply_inorder_tree(root, execute_node);
}

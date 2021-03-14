/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 09:42:32 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 23:56:55 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "libvect.h"
#include "header.h"
#include "proto.h"

const char	*print_type(t_tokentype type)
{
	static const char	*types[] = {
		"ERROR",
		"OPERATOR",
		"UNQUOTE",
		"SINGLEQUOTE",
		"DOUBLEQUOTE"
	};

	return (types[type]);
}

void	print_token(t_token token)
{
	printf("%s(%.*s) : LEN(%lu)\n",
		print_type(token.type), (int)token.length, token.start, token.length);
}


void	print_tokens(t_vect *tokens)
{
	size_t	i;
	t_token	token;

	i = 0;
	while (i < tokens->nmemb)
	{
		token = ((t_token*)tokens->table)[i];
		print_token(token);
		i++;
	}
}

void	print_args(char **args)
{
	size_t	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		printf("\t  \"%s\"\n", args[i]);
		i++;
	}
}

void	indent_depth(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("\t");
		i++;
	}
}

void	print_args_depth(char **args, int depth)
{
	size_t	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		indent_depth(depth);
		printf("  \"%s\"\n", args[i]);
		i++;
	}
}

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



void	print_node(t_node *node)
{
	if (node == NULL)
	{
		printf("Node is null\n");
		return ;
	}
	printf("\tRule: %s\n", get_rule(node->rule));
	if (node->rule == command)
		printf("\tfds[0][1]: [%d][%d]\n", node->fds[0], node->fds[1]);
	if (node->rule == command && node->args != NULL)
	{
		printf("\tARGS = {\n");
		print_args(node->args);
		printf("\t}\n");
	}
}

void	print_node_depth(t_node *node, int depth)
{
	if (node == NULL)
	{
		indent_depth(depth);
		printf("Node is null\n");
		return ;
	}
	printf("\n");
	indent_depth(depth);
	printf("\033[1;31mNODE\033[0m\n");
	indent_depth(depth);
	printf("Depth: %d:\n", depth);
	indent_depth(depth);
	printf("Rule: %s\n", get_rule(node->rule));
	if (node->rule == command)
	{
		indent_depth(depth);
		printf("fds[0][1]: [%d][%d]\n", node->fds[0], node->fds[1]);
	}
	if (node->rule == command && node->args != NULL)
	{
		indent_depth(depth);
		printf("ARGS = {\n");
		print_args_depth(node->args, depth);
		indent_depth(depth);
		printf("}\n");
	}
}


void	print_tree_depth(t_node *root, int depth)
{
	if (root == NULL)
	{
		indent_depth(depth);
		printf("Root is NULL\n");
		return ;
	}
	print_node_depth(root, depth);
	if (root->left != NULL)
		print_tree_depth(root->left, depth + 1);
	if (root->right != NULL)
		print_tree_depth(root->right, depth + 1);
}


void	print_tree(t_node *root)
{
	apply_inorder_tree(root, print_node);
}

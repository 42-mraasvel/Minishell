/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 09:42:32 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:06:38 by mraasvel      ########   odam.nl         */
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

void	print_node(t_nodex *node)
{
	static const char	*rules[] = {
		"Command",
		"Pipe",
		"Semicolon",
		"Nothing"
	};

	printf("NODE\n\t");
	print_token(node->token);
	printf("\tRule: %s\n", rules[node->rule]);
	if (node->rule == command && node->args != NULL)
	{
		printf("\tARGS = {\n");
		print_args(node->args);
		printf("\t}\n");
	}
}

void	print_tree(t_nodex *root)
{
	apply_inorder_tree(root, print_node);
}

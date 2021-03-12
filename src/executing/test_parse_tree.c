/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parse_tree.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 08:41:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:11:14 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "libvect.h"
#include "proto.h"
#include "lexer.h"
#include "tree.h"

/*
**	Example Command
**
**		a | b ; c
**
**	a: ls -la
**	b: cat -e - input.txt
**	c: echo abcde
**
**	ls = word (command)
**	-la = arg1
**
**	Tree :
**			 ;
**			/ \
**		 |		c
**		/ \
**	   a	b
*/

t_vect	*test_lexer(char *line);
void	print_tokens(t_vect *tokens);

char	**get_args(size_t n, ...)
{
	t_token	arg;
	va_list	ap;
	size_t	i;
	char	**args;

	args = malloc_guard(malloc((n + 1) * sizeof(char**)));
	va_start(ap, n);
	args[n] = NULL;
	i = 0;
	while (i < n)
	{
		arg = va_arg(ap, t_token);
		args[i] = ft_substr(arg.start, 0, arg.length);
		i++;
	}
	va_end(ap);
	return (args);
}

/*

[0] : ls
[1] : -la
[2] : |
[3] : cat
[4] : -e
[5] : -
[6] : input.txt
[7] : ;
[8] : echo
[9] : abcde

*/

t_node	*fill_tree(t_vect *tokens)
{
	t_token	*table;
	t_node	*root;

	table = (t_token*)tokens->table;
	root = new_node(table[7]);
	root->rule = semicolon;

	root->left = new_node(table[2]);
	root->left->rule = t_pipe;

	root->left->left = new_node(table[0]);
	root->left->left->rule = command;
	root->left->left->args = get_args(2, table[0], table[1]);

	root->left->right = new_node(table[3]);
	root->left->right->rule = command;
	root->left->right->args = get_args(4, table[3], table[4], table[5], table[6]);


	root->right = new_node(table[8]);
	root->right->rule = command;
	root->right->args = get_args(2, table[8], table[9]);
	return (root);
}

t_node	*example_tree(void)
{
	static char	*command = "ls -la | cat -e - input.txt ; echo abcde";
	t_vect		*tokens;
	t_node		*root;

	tokens = test_lexer(command);
	if (tokens == NULL)
		return (NULL);
	root = fill_tree(tokens);
	vect_free(tokens, NULL);
	return (root);
}

t_node	*test_parser(void)
{
	t_node	*root;

	root = example_tree();
	// print_tree(root);
	print_tree_depth(root, 0);
	// execute_tree(root);
	tree_free(root);
	return (NULL);
}

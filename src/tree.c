/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 11:28:38 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/12 14:08:25 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "libft.h"
#include "libvect.h"
#include "fcntl.h"

// typedef struct s_token
// {
// 	char		*start;
// 	size_t		length;
// 	t_tokentype	type;
// }	t_token;

t_node	*add_node(t_vect *tokens, size_t start, size_t end)
{
	t_node	*node;
	size_t	i;
	t_token	token;
	int		give_birth;

	node = (t_node*)malloc(1 * sizeof(t_node));
	if (node == 0)
		return (0);
	if (start = end)
		return (0);
	i = start;
	give_birth = 0;
	while (i < end && !give_birth)
	{
		if (*((t_token*)tokens->table)[i].start == ';')
		{
			give_birth = 1;
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i, end);
			node->rule = semicolon;
		}
		i++;
	}
	i = start;
	while (i < end && !give_birth)
	{
		if (*((t_token*)tokens->table)[i].start == '|')
		{
			give_birth = 1;
			node->left = add_node(tokens, start, i);
			node->right = add_node(tokens, i, end);
			node->rule = t_pipe;
		}
		i++;
	}
	if (!give_birth)
	{
		node->rule = command;
		node->left = 0;
		node->right = 0;
		node->fds[0] = -1;
		node->fds[1] = -1;
		i = start;
		node->args = malloc(1 + (start - end) * sizeof(char *));
		if (node->args == 0)
			return (0);	
		while (i < tokens->nmemb)
		{
			node->args[i] = ((t_token*)tokens->table)[i].start;
			if (i > 0 && ft_strnstr(node->args[i - 1], ">>", 2))
				node->fds[1] = open(node->args[i], (O_APPEND | O_CREAT));
			else if (i > 0 && *node->args[i - 1] == '>')
				node->fds[1] = open(node->args[i], (O_WRONLY | O_CREAT));
			else if (i > 0 && *node->args[i - 1] == '<')
				node->fds[0] = open(node->args[i], O_RDONLY);
			i++;
		}
		node->args[i] = 0;
	}
	return (node);
}

t_node	*create_tree(t_vect *tokens)
{
	t_node	*tree;

	tree = add_node(tokens, 0, tokens->nmemb);
	return (tree);
}

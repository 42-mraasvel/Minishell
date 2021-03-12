/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 13:07:10 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "lexer.h"

typedef enum e_rule
{
	command,
	t_pipe,
	semicolon,
}	t_rule;

typedef struct s_node
{
	t_rule			rule;
	char			**args;
	int				fds[2];
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

#endif

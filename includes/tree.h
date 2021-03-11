/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tree.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/11 16:42:19 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "lexer.h"

typedef struct s_node
{
	t_token			token;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

#endif

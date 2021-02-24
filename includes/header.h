/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:46:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/02/24 17:51:56 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef enum e_ntype
{
	
}	t_ntype;

typedef struct s_node
{
	int				type;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif

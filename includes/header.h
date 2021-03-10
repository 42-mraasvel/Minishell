/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:46:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/10 13:31:09 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

// # define MINISHELL_PROMPT "\033[1;33m>\033[0m "
# define MINISHELL_PROMPT "\033[1;33mminishell$\033[0m "

typedef enum e_errnum
{
	error,
	success
}	t_errnum;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_node
{
	int				type;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif

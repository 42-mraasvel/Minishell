/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:46:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:10:05 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "lexer.h"

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



// typedef enum e_rule
// {
// 	command,
// 	t_pipe,
// 	semicolon,
// 	nothing
// }	t_rule;

// typedef struct s_nodex
// {
// 	t_token			token;
// 	char			**args;
// 	t_rule			rule;
// 	int				fds[2];
// 	struct s_nodex	*right;
// 	struct s_nodex	*left;
// }	t_nodex;

#endif

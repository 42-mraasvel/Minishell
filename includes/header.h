/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:46:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 20:33:39 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "lexer.h"

// # define MINISHELL_PROMPT "\033[1;33m>\033[0m "
# define MINISHELL_PROMPT "\033[1;33mminishell$\033[0m "

typedef enum e_errnum
{
	success = 0,
	error,
	syntax_error,
	open_error,
	malloc_error
}	t_errnum;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_data
{
	t_errnum	errnum;
}	t_data;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 13:57:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libvect.h"

typedef enum e_errnum
{
	success = 0,
	error,
	syntax_error,
	open_error,
	malloc_error,
	syscall_error,
	cmd_not_found
}	t_errnum;

typedef enum e_bool
{
	false,
	true
}	t_bool;

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

typedef struct s_error
{
	t_errnum	errnum;
	char		*err_str;
}	t_error;

typedef struct s_data
{
	t_error		error;
	t_vect		*exec_errors;
	t_vect		*tokens;
	t_node		*root;
	char		**envp;
	int			exit_status;
}	t_data;

#endif

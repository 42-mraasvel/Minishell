/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:25:57 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libvect.h"
# include "lexer.h"
# include "ft_termcap.h"

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
	ft_false,
	ft_true
}	t_bool;

typedef enum e_rule
{
	command,
	t_pipe,
	semicolon,
}	t_rule;

typedef struct s_cmd
{
	t_vect	*output_files;
}	t_cmd;

/*
** Redirects = t_token *
*/

typedef struct s_node
{
	t_rule			rule;
	char			**args;
	char			*exec_path;
	int				fds[2];
	t_vect			*redirects;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

typedef struct s_error
{
	t_errnum	errnum;
	char		*err_str;
}	t_error;

typedef enum e_ptype
{
	builtin,
	p_command,
	p_error
}	t_ptype;

typedef struct s_process
{
	t_ptype	ptype;
	int		pid;
	int		exit_status;
}	t_process;

typedef struct s_data
{
	t_error		error;
	t_vect		*exec_errors;
	t_vect		*tokens;
	t_node		*root;
	t_vect		*processes;
	t_termcap	term;
	t_rule		executor_status;
	int			interrupted;
	char		**envp;
	char		***envpp;
	int			exit_status;
}	t_data;

#endif

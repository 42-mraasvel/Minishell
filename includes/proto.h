/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 18:01:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/10 21:25:45 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "header.h"
# include "libvect.h"


void test_pipe();

/* Lexing part */

t_vect	*lexer(char *line);

size_t	tokenize_operator(char *start);
size_t	tokenize_word(char *start);
size_t	tokenize_squote(char *start);
size_t	tokenize_dquote(char *start);
size_t	tokenize_variable(char *start);

/* lexer_utils.c */

t_bool	is_operator(char c);
t_bool	is_metachar(char c);
size_t	is_double(char *start);

/* Some wrappers, quality of life functions */

void	*malloc_guard(void *malloc_return);


/* error part : exit_program.c */

void	exit_program(t_errnum errnum, char *err_str);

#endif

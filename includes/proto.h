/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 18:01:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/12 14:03:40 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "header.h"
# include "libvect.h"
# include "tree.h"


void	test_pipe(void);

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
char	*get_path(void);
int		file_exists(char *filename);

/* Some Tree Functions To Test Executor */

t_nodex	*test_parser(void);

void	execute_tree(t_nodex *root);
void	exec_pipe(t_nodex *node);
void	exec_command(t_nodex *node);

t_nodex	*new_node(t_token data);
void	tree_free(t_nodex *root);
void	apply_inorder_tree(t_nodex *root, void (*fct)(t_nodex *));

/* error part : exit_program.c */

void	exit_program(t_errnum errnum, char *err_str);

/* Printing Stuff */

void	print_tokens(t_vect *tokens);
void	print_token(t_token token);
void	print_node(t_nodex *node);
void	print_tree(t_nodex *root);
void	print_tree_depth(t_nodex *root, int depth);

#endif

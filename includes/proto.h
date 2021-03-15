/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 18:01:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 23:11:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "header.h"
# include "libvect.h"
# include "tree.h"


int		prompt(t_data *data);

void	test_pipe(void);

/* Lexing part */

t_vect	*lexer(char *line, t_data *data);
t_token	lex_word(char *line);
t_token	lex_operator(char *line);

/* lexer_utils.c */

t_bool	ismeta(char c);
char	*skipspace(char *line);
t_bool	isquote(char c);

/* Some wrappers, quality of life functions */

void	*malloc_guard(void *malloc_return);
char	*get_path(void);
int		file_exists(char *filename);
void	set_err_data(t_data *data, t_errnum errnum, char *err_str);
void	*set_err_data_null(t_data *data, t_errnum errnum, char *err_str);

/* Some Tree Functions To Test Executor */

t_node	*create_tree(t_vect *tokens);

t_node	*test_parser(void);

void	execute_tree(t_node *root);
void	exec_pipe(t_node *node);
void	exec_command(t_node *node);

t_node	*new_node(t_token data);
void	tree_free(t_node *root);
void	apply_inorder_tree(t_node *root, void (*fct)(t_node *));

/* error part : exit_program.c */

void	exit_program(t_errnum errnum, char *err_str);

/* Printing Stuff */

void	print_tokens(t_vect *tokens);
void	print_token(t_token token);
void	print_node(t_node *node);
void	print_tree(t_node *root);
void	print_tree_depth(t_node *root, int depth);

#endif

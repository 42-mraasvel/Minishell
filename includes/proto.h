/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 18:01:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/18 09:34:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "structs.h"
# include "libvect.h"
# include "structs.h"
# include "lexer.h"

int		prompt(t_data *data);

void	test_pipe(void);

/* Lexing part */

t_vect	*lexer(char *line, t_data *data);
t_token	lex_word(char *line);
t_token	lex_operator(char *line);

/* lexer_utils.c */

char	*skipspace(char *line);

/* isfunctions */

t_bool	ismeta(char c);
t_bool	isquote(char c);
t_bool	isalphanumscore(char c);
t_bool	isalphascore(char c);

/* Some wrappers, quality of life functions */

void	*malloc_guard(void *malloc_return);
char	*get_path(void);
int		file_exists(char *filename);

/* Utils */

int		get_envp(t_data *data);

/* Error Handling */

int		syntax_check(t_data *data, t_vect *tokens); //! Checks if tokens are valid

void	flush_error(t_data *data);

void	set_err_data(t_data *data, t_errnum errnum);
void	*set_err_data_null(t_data *data, t_errnum errnum);
int		set_err_data_int(t_data *data, t_errnum errnum, int ret);
int		set_error_vec(t_data *data, t_errnum errnum, char *str, int ret);

/* Expander */

int		expander(t_data *data);
void	expand_word(t_data *data, t_token *token);

/* Some Tree Functions To Test Executor */

t_node	*create_tree(t_vect *tokens);
t_node	*add_node(t_vect *tokens, size_t start, size_t end);

t_node	*test_parser(void);

int		executor(t_node *root, t_data *data);
int		exec_pipe(t_node *node, t_data *data);
int		exec_command(t_node *node, t_data *data);

int		lookup_path(t_data *data, char **args, char *name);

void	tree_free(t_node *root);
void	apply_prefix_tree(t_node *root, void (*fct)(t_node *));
int		apply_prefix_tree_data(
			t_node *root, t_data *data, int (*fct)(t_node *, t_data *));

/* Builtin Functions */

int		call_builtins(t_data *data, t_node *node);

int		ft_echo(char **args);
int		ft_env(t_data *data);
int		ft_pwd(char **args);
int		ft_unset(t_data *data, char **args);
int		ft_export(t_data *data, char **args);

/* Env Utils */

t_bool	isvalidvar(char *var);
t_bool	isvalidvar_asign(char *arg);
t_bool	varinargs(char *var, char **args, char arg_end);

/* error part : exit_program.c */

void	exit_program(t_errnum errnum, char *err_str);

/* Printing Stuff */

void	print_tokens(t_vect *tokens);
void	print_token(t_token token);
void	print_node(t_node *node);
void	print_tree(t_node *root);
void	print_tree_depth(t_node *root, int depth);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 18:01:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 15:16:31 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "structs.h"
# include "libvect.h"
# include "structs.h"
# include "lexer.h"

int		prompt(t_data *data);
int		process_cli(char *line, t_data *data);
t_data	*getdata(void);

void	test_pipe(void);

/* Lexing part */

t_vect	*lexer(char *line, t_data *data);
t_token	lex_word(char *line);
t_token	lex_operator(char *line);

/* lexer_utils.c */

char	*skipspace(char *line);
int		allocate_tokens(t_data *data);

/* isfunctions */

t_bool	ismeta(char c);
t_bool	isquote(char c);
t_bool	isalphanumscore(char c);
t_bool	isalphascore(char c);

/* Some wrappers, quality of life functions */

void	*malloc_guard(void *malloc_return);
void	*ft_malloc(size_t size);
char	*get_path(void);
int		file_exists(char *filename);
t_bool	isdir(char *filename);

/* Utils */

int		get_envp(t_data *data);
int		*get_exit_status(void);
void	ft_putprompt(char *prefix);

/* Error Handling */

int		syntax_check(t_data *data, t_vect *tokens);

void	flush_error(t_data *data);

void	set_err_data(t_data *data, t_errnum errnum);
void	*set_err_data_null(t_data *data, t_errnum errnum);
int		set_err_data_int(t_data *data, t_errnum errnum, int ret);
int		set_error_vec(t_data *data, t_errnum errnum, char *str, int ret);

/* Some Tree Functions To Test Executor */

t_node	*create_tree(t_vect *tokens);
t_node	*add_node(t_vect *tokens, size_t start, size_t end);

int		check_semicolon(t_vect *tokens, size_t start, size_t end, t_node *node);
int		check_pipe(t_vect *tokens, size_t start, size_t end, t_node *node);
int		check_for_redirect(
			t_token *curr, t_token *next, t_node *node, size_t *index);

int		executor(t_node *root, t_data *data);
int		execute_node(t_node *node, t_data *data);
int		exec_pipe(t_node *node, t_data *data);
int		exec_command(t_node *node, t_data *data);
int		exec_semicolon(t_node *node, t_data *data);

void	close_fds(t_node *node);
int		isbuiltin(char *arg);
int		lookup_path(t_data *data, char **args, char *name);

void	tree_free(t_node *root);
void	apply_prefix_tree(t_node *root, void (*fct)(t_node *));
int		apply_prefix_tree_data(
			t_node *root, t_data *data, int (*fct)(t_node *, t_data *));

/* Builtin Functions */

int		call_builtins(t_data *data, t_node *node);

int		ft_echo(t_data *data, char **args);
int		ft_cd(t_data *data, char **args);
int		ft_pwd(t_data *data, char **args);
int		ft_export(t_data *data, char **args);
int		ft_export_print(t_data *data);
int		ft_unset(t_data *data, char **args);
int		ft_env(t_data *data, char **args);
int		ft_exit(t_data *data, char **args);

/* Env Utils */

t_bool	isvalidvar(char *var);
t_bool	isvalidvar_asign(char *arg);
t_bool	varinargs(char *var, char **args, char arg_end);

/* error part : exit_program.c */

void	ft_perror(char *str);
void	ft_error(char *prefix, char *str);
void	end_program(t_data *data);
void	exit_program(t_errnum errnum, char *err_str);
void	exit_perror(int exit_status, char *str);

/* Printing Stuff */

void	print_tokens(t_vect *tokens);
void	print_token(t_token token);
void	print_node(t_node *node);
void	print_command(t_node *node);
void	print_tree(t_node *root);
void	print_tree_depth(t_node *root, int depth);

/* Termcaps */

int		prompt_termcap(t_data *data);
int		init_termcap(t_data *data);
int		ft_setterm(t_data *data, int reset);
void	restore_term(t_data *data);
void	delete_edited(t_tchist *hist);
void	reset_term(void);
int		save_newest(char *str, t_tchist *hist);
char	*cycle_through(t_tchist *hist, int up, int down);

void	termcmd(char *id, int hpos, int ypos, int nlines);
void	delete_char(t_data *data);

t_bool	buffer_is_empty(t_data *data);
void	put_line(char *str, t_cursor *cursor);
void	pushback_char(t_data *data, char c);
void	pop_char(t_data *data);
void	pop_line(t_data *data);
void	flush_line(t_data *data);

/* Cursor */

void	cursor_update(t_data *data);
void	cursor_move(t_cursor *cursor, t_point delta);
void	update_winsz(void);
void	clear_line(t_data *data);

void	print_cursor(t_cursor cursor);

/* Point */

t_point	point(int x, int y);
t_point	point_sub(t_point a, t_point b);
t_point	point_add(t_point a, t_point b);

#endif

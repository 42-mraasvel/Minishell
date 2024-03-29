/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 18:52:34 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stddef.h>
# include "structs.h"
# include "vec_string.h"

/* Expander */

int		expander(t_data *data);

int		expand_node(t_node *node);
int		expand_args(t_node *node);
t_vect	*expand_parameters(char **args);
void	expand_arg(t_vect *strings, char *arg);
int		expand_redirects(t_node *node);

char	*get_variable(char *arg, size_t *lenptr);

size_t	expand_char(t_vect *strings, t_vecstr *string, char *arg);
size_t	expand_exit_status(t_vecstr *string, char *arg);
size_t	expand_variable(t_vect *strings, t_vecstr *string, char *arg);
size_t	expand_tilde(t_vect *strings, t_vecstr *string, char *arg);
size_t	expand_squote(t_vect *strings, t_vecstr *string, char *arg);
size_t	expand_dquote(t_vect *strings, t_vecstr *string, char *arg);

typedef size_t	(*t_expander)(t_vect *, t_vecstr *, char *);

#endif

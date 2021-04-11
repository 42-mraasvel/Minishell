/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 17:54:26 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

typedef int	(*t_builtin)(t_data *, char **);
typedef int	(*t_redirfct)(t_node *, char *);

int		isbuiltin(char *arg);
int		exec_builtin(t_node *node, t_data *data);

int		cmd_redirects(t_node *node);
void	search_path(t_data *data, char **dst, char *name);

void	new_process(t_data *data, t_ptype type, int value);
void	reset_processes(t_data *data);
void	kill_processes(t_data *data, size_t i);

#endif

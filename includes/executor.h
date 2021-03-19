/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/19 08:17:38 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

typedef int	(*t_builtin)(t_data *, char **);

int	isbuiltin(char *arg);
int	exec_builtin(t_node *node, t_data *data);

#endif

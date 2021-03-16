/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 09:41:26 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stddef.h>
# include "structs.h"
# include "vec_string.h"

typedef size_t	(*t_expander)(t_data *, t_vecstr *, char *);

t_expander	get_expander(size_t i);
size_t		expand_char(t_data *data, t_vecstr *result, char c);
size_t		expand_home(t_data *data, t_vecstr *result, char *str);

#endif

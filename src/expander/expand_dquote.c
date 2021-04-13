/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dquote.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 20:30:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 15:00:20 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "header.h"
#include "libft.h"
#include "proto.h"
#include "expander.h"
#include "vec_string.h"
#include "structs.h"

static t_bool	dq_isonlyvariable(char *arg, size_t len, size_t var_len)
{
	if (arg[var_len + 1] != '\0' || len > 1 || arg[var_len] != '"')
		return (ft_false);
	return (ft_true);
}

/*
** Options:
**	1. "$?"
**	2. "$<non_alscore>"
**	3. "$<variable>"
**	4. "$<variable_no_value>"
*/

static size_t	expand_dquote_variable(t_vect *strings, t_vecstr *string,
					char *arg, size_t len)
{
	char	*value;
	size_t	var_len;

	if (arg[1] == '?')
		return (expand_exit_status(string, arg));
	if (!isalphascore(arg[1]))
		return (expand_char(strings, string, arg));
	value = get_variable(arg, &var_len);
	if (value == NULL || *value == '\0')
	{
		if (dq_isonlyvariable(arg, len, var_len) && string->len == 1)
			expand_char(strings, string, "");
	}
	else if (vecstr_pushback_str(string, value) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (var_len);
}

size_t	expand_dquote(t_vect *strings, t_vecstr *string, char *arg)
{
	size_t	len;

	len = 1;
	if (arg[len] == '"')
		return (expand_char(strings, string, "") + 1);
	while (arg[len] != '"')
	{
		if (arg[len] == '$')
			len += expand_dquote_variable(strings, string, &arg[len], len);
		else
			len += expand_char(strings, string, arg + len);
	}
	return (len + 1);
}

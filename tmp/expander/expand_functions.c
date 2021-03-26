/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 09:28:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/22 11:31:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> // rm
#include "libft.h"
#include "expander.h"
#include "proto.h"

static size_t	expand_exit_status(t_data *data, t_vecstr *result, char *str)
{
	char	*num;

	num = ft_itoa(data->exit_status);
	if (num == NULL)
		return (set_err_data_int(data, malloc_error, 0));
	if (vecstr_pushback_str(result, num) == -1)
		set_err_data_int(data, malloc_error, 0);
	free(num);
	return (2);
}

static size_t	expand_variable(t_data *data, t_vecstr *result, char *str)
{
	size_t	len;
	char	*var[2];

	len = 1;
	if (str[len] == '?')
		return (expand_exit_status(data, result, str));
	if (!isalphascore(str[len]))
		return (expand_char(data, result, str[0]));
	while (isalphanumscore(str[len]))
		len++;
	var[0] = ft_substr(str, 1, len - 1);
	if (var[0] == NULL)
		return (set_err_data_int(data, malloc_error, 0));
	var[1] = getenv(var[0]);
	free(var[0]);
	if (var[1] == NULL)
		return (len);
	if (vecstr_pushback_str(result, var[1]) == -1)
		return (set_err_data_int(data, malloc_error, 0));
	return (len);
}

static size_t	expand_dquote(t_data *data, t_vecstr *result, char *str)
{
	size_t	i;

	i = 1;
	while (str[i] != '"')
	{
		if (str[i] == '$')
			i += expand_variable(data, result, str + i);
		else
			i += expand_char(data, result, str[i]);
	}
	return (i + 1);
}

static size_t	expand_squote(t_data *data, t_vecstr *result, char *str)
{
	char	*ptr;

	ptr = ft_strchr(str + 1, '\'');
	if (vecstr_pushback_substr(result, str + 1, ptr - str - 1) == -1)
		return (set_err_data_int(data, malloc_error, 0));
	return ((ptr - str) + 1);
}

t_expander	get_expander(size_t i)
{
	static t_expander	expand[255] = {
		['$'] = expand_variable,
		['"'] = expand_dquote,
		['\''] = expand_squote,
		['~'] = expand_home
	};

	return (expand[i]);
}

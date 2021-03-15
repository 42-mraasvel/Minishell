/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_word.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 19:22:54 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 21:55:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vec_string.h"
#include "lexer.h"
#include "libft.h"
#include "structs.h"
#include "proto.h"

static size_t	expand_char(t_data *data, t_vecstr *result, char c)
{
	if (vecstr_pushback_c(result, c) == -1)
		return (set_err_data_int(data, malloc_error, 0));
	return (1);
}

static size_t	expand_variable(t_data *data, t_vecstr *result, char *str)
{
	size_t	len;
	char	*var[2];

	len = 1;
	// if (str[len] == '?')
		//! Expand exit status;
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

/*
** Create new allocated string
** With all values expanded
** Replace old token string with new one.
*/

void	expand_word(t_data *data, t_token *token)
{
	t_vecstr	*result;
	size_t		i;

	result = vecstr_init(token->length + 1);
	if (result == NULL)
		return (set_err_data(data, malloc_error));
	i = 0;
	while (i < token->length)
	{
		if (token->start[i] == '$')
			i += expand_variable(data, result, token->start + i);
		else if (token->start[i] == '"')
			i += expand_dquote(data, result, token->start + i);
		else if (token->start[i] == '\'')
			i += expand_squote(data, result, token->start + i);
		else
			i += expand_char(data, result, token->start[i]);
		if (data->error.errnum != success)
			break ;
	}
	token->length = result->len - 1;
	token->start = result->str;
	if (data->error.errnum != success)
		free(result->str);
	free(result);
}

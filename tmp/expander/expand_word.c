/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_word.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 19:22:54 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/23 19:43:54 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander.h"
#include "lexer.h"
#include "libft.h"
#include "proto.h"

size_t	expand_home(t_data *data, t_vecstr *result, char *str)
{
	char	*var;

	var = getenv("HOME");
	if (var == NULL)
	{
		vecstr_pushback_c(result, '~');
		return (1);
	}
	if (vecstr_pushback_str(result, var) == -1)
		return (set_err_data_int(data, malloc_error, 0));
	return (1);
}

size_t	expand_char(t_data *data, t_vecstr *result, char c)
{
	if (vecstr_pushback_c(result, c) == -1)
		return (set_err_data_int(data, malloc_error, 0));
	return (1);
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
	t_expander	expand;

	result = vecstr_init(token->length + 1);
	if (result == NULL)
		return (set_err_data(data, malloc_error));
	i = 0;
	while (i < token->length)
	{
		expand = get_expander(token->start[i]);
		if (expand == NULL)
			i += expand_char(data, result, token->start[i]);
		else
			i += expand(data, result, token->start + i);
		if (data->error.errnum != success)
			break ;
	}
	token->length = result->len - 1;
	token->start = result->str;
	if (data->error.errnum != success)
		free(result->str);
	free(result);
}

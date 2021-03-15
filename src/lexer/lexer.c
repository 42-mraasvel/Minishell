/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 23:24:47 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 11:56:27 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "proto.h"

static t_vect	*check_tokens(t_vect *tokens, t_data *data)
{
	if (data->error.errnum != success || tokens->nmemb == 0)
	{
		vect_free(tokens, NULL);
		return (NULL);
	}
	return (tokens);
}

static size_t	next_token(char *line, t_vect *tokens, t_data *data)
{
	t_token	token;

	if (ismeta(*line))
		token = lex_operator(line);
	else
		token = lex_word(line);
	if (vect_pushback(tokens, &token) == -1)
		set_err_data(data, malloc_error);
	return (token.length);
}

t_vect	*lexer(char *line, t_data *data)
{
	t_vect	*tokens;

	tokens = vect_init(10, sizeof(t_token));
	if (tokens == NULL)
		return (set_err_data_null(data, malloc_error));
	while (*line != '\0')
	{
		line = skipspace(line);
		if (*line == '\0')
			break ;
		line += next_token(line, tokens, data);
		if (data->error.errnum != success)
			break ;
	}
	return (check_tokens(tokens, data));
}

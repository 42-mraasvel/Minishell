/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_word.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 22:21:57 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 23:10:59 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "proto.h"
#include "lexer.h"

static size_t	skipquote(char *start)
{
	size_t	i;

	i = 1;
	while (start[i] && start[i] != *start)
		i++;
	return (i);
}

static t_token	error_token(t_token token)
{
	token.type = bad_token;
	return (token);
}

t_token	lex_word(char *line)
{
	t_token	token;

	token.start = line;
	token.length = 0;
	token.type = word;
	while (line[token.length] && !ismeta(line[token.length]))
	{
		if (isquote(line[token.length]))
		{
			token.length += skipquote(line + token.length);
			if (line[token.length] == '\0')
				return (error_token(token));
			token.length += 1;
			continue ;
		}
		token.length++;
	}
	return (token);
}

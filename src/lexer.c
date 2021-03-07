/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 12:39:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/06 14:29:29 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "proto.h"

/*
** 1. Check type of token
*/

t_tokentype	get_token_type(char c)
{
	if (is_operator(c))
		return (operator);
	return (bad_token);
	// else if (c == '"')
	// 	return (double_quoted);
	// else if (c == '\'')
	// 	return (single_quoted);
	// else
	// 	return (unquoted);
}

size_t	parse_token(t_token *token)
{
	static const t_tokenizer	tokenizers[] = {
		tokenize_operator,
		tokenize_word,
		tokenize_squote,
		tokenize_dquote
	};

	token->type = get_token_type(*(token->start));
	token->length = tokenizers[token->type](token->start);
	return(token->length);
}

t_bool	next_token(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '#' || **line == '\0')
		return (false);
	return (true);
}

/*
** 1. find start of next token
** 2. types of starts:
**		Operator
**		Quote start
**		Word start
**
*/

t_vect	*lexer(char *line)
{
	t_vect	*tokens;
	t_token	token;

	tokens = malloc_guard(vect_init(0, sizeof(t_token)));
	while (next_token(&line))
	{
		token.start = line;
		line += parse_token(&token);
		if (vect_pushback(tokens, &token) == -1)
		{
			vect_free(tokens, NULL);
			return (NULL);
		}
	}
	return (tokens);
}

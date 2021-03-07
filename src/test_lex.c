/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_lex.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 23:24:47 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/06 17:41:01 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "libft.h"
#include "proto.h"

const char	*print_type(t_tokentype type)
{
	static const char	*types[] = {
		"ERROR",
		"OPERATOR",
		"WORD"
	};

	return (types[type]);
}

void	print_tokens(t_vect *tokens)
{
	size_t	i;
	t_token	token;

	i = 0;
	while (i < tokens->nmemb)
	{
		token = ((t_token*)tokens->table)[i];
		printf("%s(%.*s) : LEN(%lu)\n", print_type(token.type), (int)token.length, token.start, token.length);
		i++;
	}
}

char	*skipspace(char *line)
{
	//! Skip only space + tabs, or all whitespace as defined in POSIX?
	while (ft_isspace(*line))
		line++;
	// while (*line == ' ' || *line == '\t')
	// 	line++;
	return (line);
}

/*
<metacharacter>	::=	::=	'|'
					|	'<'
					|	'>'
					|	';'
					|	<blank>
					|	'\n' (newline)
				NOT IN SUBJECT:
					|	'&'
					|	'('
					|	')'
*/

t_bool	ismeta(char c)
{
	static const char	*meta = "|<>; \t\n";

	if (ft_strchr(meta, c) == NULL)
		return (false);
	return (true);
}

t_token	parse_operator(char *line)
{
	t_token	token;

	token.start = line;
	token.length = 0;
	token.type = operator;
	token.length = 1;
	if (*line == '>' && *(line + 1) == '>')
		token.length += 1;
	return (token);
}

t_token	parse_error(char *line, t_token token)
{
	token.type = bad_token;
	token.length = ft_strlen(line);
	return (token);
}

t_token	parse_quotes(char *line, t_token token)
{
	char	*ptr;

	ptr = ft_strchr(line + 1, *line);
	if (ptr == NULL)
		return (parse_error(line, token));
	token.length = ptr - line + 1;
	return (token);
}

t_token	parse_word(char *line)
{
	t_token	token;

	token.start = line;
	token.length = 0;
	token.type = word;
	if (*line == '\'' || *line == '"')
		return (parse_quotes(line, token));
	while (!ismeta(*(line + token.length)))
		token.length++;
	return (token);
}

t_vect	*test_lexer(char *line)
{
	t_vect	*tokens;
	t_token	token;

	printf("Lexing: %s\n", line);
	tokens = malloc_guard(vect_init(0, sizeof(t_token)));
	while (1)
	{
		line = skipspace(line);
		if (*line == '\0')
			return (tokens);
		if (ismeta(*line))
			token = parse_operator(line);
		else
			token = parse_word(line);
		if (vect_pushback(tokens, &token) == -1)
		{
			vect_free(tokens, NULL);
			exit_program(error, "Pushback failed\n");
		}
		line += token.length;
	}
	return (tokens);
}

void	test_lex()
{
	int		ret;
	char	*line;
	t_vect	*tokens;

	ret = 1;
	while (ret > 0)
	{
		ft_putstr(MINISHELL_PROMPT);
		ret = ft_getline(0, &line);
		if (ret < 0)
			exit_program(error, "Getline error");
		tokens = test_lexer(line);
		print_tokens(tokens);
		vect_free(tokens, NULL);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_operator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 22:23:13 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/26 10:38:01 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static t_optype	get_optype(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (redirect_append);
	else if (*line == '<')
		return (redirect_in);
	else if (*line == '>')
		return (redirect_out);
	else if (*line == '|')
		return (o_pipe);
	else if (*line == ';')
		return (o_semicolon);
	else
		return (non_operator);
}

t_token	lex_operator(char *line)
{
	t_token	token;

	token.start = line;
	token.type = operator;
	token.length = 1;
	token.optype = get_optype(line);
	if (token.optype == redirect_append)
		token.length += 1;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_operator.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 22:23:13 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 23:10:46 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static t_optype	get_optype(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (redirect_append);
	return (ft_strchri("<>;|", *line));
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

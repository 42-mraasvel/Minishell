/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 13:54:31 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 18:38:28 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include "libft.h"
#include "lexer.h"
#include "structs.h"



static void	put_syntax_error(t_token token)
{
	// "-bash: syntax error near unexpected token `>'"
	// "-bash: syntax error near unexpected token `;'"
	ft_putstr_fd("-bash: syntax error near unexpected token ", STDERR_FILENO);
	write(STDERR_FILENO, token.start, token.length);
	write(STDERR_FILENO, "\n", 1);
}

static int	check_operator(t_token *token, t_optype prev, size_t i, size_t max)
{
	if (token->optype == semicolon && i == 0)
		return (syntax_error);
	if (token->optype == o_pipe && i == 0)
		return (syntax_error);
	return (success);
}

/*
** Errors:
**
** No "word" Token after following:
**	>
**	>>
**	<
**	|
** No "word" Token before following:
**	;
*/

int	syntax_check(t_data *data, t_vect *tokens)
{
	t_token		*table;
	size_t		i;
	t_optype	prev_optype;

	i = 0;
	table = (t_token*)tokens->table;
	prev_optype = non_operator;
	while (i < tokens->nmemb)
	{
		if (table[i].type != word)
			if (check_operator(
					&table[i], prev_optype, i, tokens->nmemb) != success)
			{
				put_syntax_error(table[i]);
				return (syntax_error);
			}
		i++;
	}
	return (success);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 13:54:31 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/22 11:30:14 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "structs.h"

static int	ft_isotherop(t_optype type)
{
	if (type == semicolon || type == non_operator)
		return (false);
	return (true);
}

static int	syntax_op_error(t_token token, t_optype prev, size_t left)
{
	ft_putstr_fd("-bash: syntax error near unexpected token `", STDERR_FILENO);
	if (left == 0 && ft_isotherop(token.optype) && !ft_isotherop(prev))
		write(STDERR_FILENO, "newline", 7);
	else
		write(STDERR_FILENO, token.start, token.length);
	write(STDERR_FILENO, "'\n", 2);
	return (syntax_error);
}

static int	check_operator(t_token *token, t_optype prev, size_t i, size_t max)
{
	if (token->optype == semicolon && (i == 0 || prev != non_operator))
		return (syntax_error);
	if (token->optype == o_pipe && i == 0)
		return (syntax_error);
	if (ft_isotherop(prev))
		return (syntax_error);
	if (ft_isotherop(token->optype) && i == max - 1)
		return (syntax_error);
	return (success);
}

static int	syntax_error_token(t_token *token)
{
	ft_putstr_fd("-bash: syntax error: ", STDERR_FILENO);
	write(STDERR_FILENO, token->start, token->length);
	write (STDERR_FILENO, "\n", 1);
	return (syntax_error);
}

/*
** Errors:
**
** (?) = operator or nothing
**	> (?)
**	>> (?)
**	< (?)
**	(?) | (?)
**	(?) ;
** token = error type (unclosed quotes)
*/

int	syntax_check(t_data *data, t_vect *tokens)
{
	t_token		*table;
	size_t		i;
	t_optype	prev;

	i = 0;
	table = (t_token *)tokens->table;
	prev = non_operator;
	while (i < tokens->nmemb)
	{
		if (table[i].type == operator)
		{
			if (check_operator(&table[i], prev, i, tokens->nmemb) != success)
				return (syntax_op_error(table[i], prev, tokens->nmemb - i - 1));
		}
		else if (table[i].type == bad_token)
			return (syntax_error_token(&table[i]));
		prev = table[i].optype;
		i++;
	}
	return (success);
}

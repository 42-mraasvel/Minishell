/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexerutils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:19:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/13 00:02:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "proto.h"

size_t	is_double(char *start)
{
	static const char	*doubles[] = {
		"||",
		"&&",
		";;",
		";&",
		";;&",
		"|&",
		NULL
	};
	size_t	i;
	size_t	len;

	i = 0;
	while (doubles[i] != NULL)
	{
		len = ft_strlen(doubles[i]);
		if (ft_strncmp(doubles[i], start, len) == 0)
			return (len);
		i++;
	}
	return (1);
}

/*
** Operators:
	control operator
		A token that performs a control function.
		It is a newline or one of the following:
		‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.

	operator
		A control operator or a redirection operator.
		See Redirections, for a list of redirection operators.
		Operators contain at least one unquoted metacharacter.
*/

t_bool	is_operator(char c)
{
	static const char	*operators = "|&;()<>";

	if (ft_strchr(operators, c) != NULL)
		return (true);
	return (false);
}

/*
	metacharacter
		A character that, when unquoted, separates words.
		A metacharacter is a space(' '), tab ('\t'), newline('\n'), or one of the following characters:
		‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
*/

t_bool	is_metachar(char c)
{
	static const char	*metachars = "|&;()<>\t\n ";

	if (ft_strchr(metachars, c) != NULL)
		return (true);
	return (false);
}

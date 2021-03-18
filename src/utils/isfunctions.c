/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isfunctions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 19:37:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/18 08:30:10 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

/*
** [0-9] | [a-zA-Z] | '_'
*/

t_bool	isalphascore(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (true);
	return (false);
}

t_bool	isalphanumscore(char c)
{
	if (isalphascore(c) || ft_isdigit(c))
		return (true);
	return (false);
}

t_bool	ismeta(char c)
{
	if (c == '\0')
		return (false);
	if (ft_strchr("|<>; \t\n", c) == NULL)
		return (false);
	return (true);
}

t_bool	isquote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isfunctions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 19:37:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/06 17:29:04 by mraasvel      ########   odam.nl         */
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
		return (ft_true);
	return (ft_false);
}

t_bool	isalphanumscore(char c)
{
	if (isalphascore(c) || ft_isdigit(c))
		return (ft_true);
	return (ft_false);
}

t_bool	ismeta(char c)
{
	if (c == '\0')
		return (ft_false);
	if (ft_strchr("|<>; \t\n", c) == NULL)
		return (ft_false);
	return (ft_true);
}

t_bool	isquote(char c)
{
	if (c == '\'' || c == '"')
		return (ft_true);
	return (ft_false);
}

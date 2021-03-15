/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 22:23:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 09:16:53 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

char	*skipspace(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
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

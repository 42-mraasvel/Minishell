/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 22:23:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:58:10 by mraasvel      ########   odam.nl         */
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

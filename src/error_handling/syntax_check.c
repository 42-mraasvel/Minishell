/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 13:54:31 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/16 14:25:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "structs.h"

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

int	syntax_check(t_data *data)
{
	t_token	*table;
	size_t	i;

	table = data->tokens->table;
	i = 0;
	while (i < data->tokens->nmemb)
	{
		i++;
	}
	return (0);
}

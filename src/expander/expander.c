/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 13:29:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 13:33:49 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/*
** Expand all WORD types in TOKENS
**
** Supported Expansions:
** 	Environment variables
** 	$? $<ENV>
** Unsupported:
**	${<ENV>}
**	Non-export variables
*/

int	expander(t_data *data)
{
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 13:19:37 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/17 13:27:17 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include "structs.h"

/*
** Outcomes:
**	0. No arguments
**	1. New variables
**	2. Replace existing variables
**	3. Invalid variable names
*/

int	ft_export(t_data *data, char **args)
{
	if (*args == NULL)
		return (ft_env(data));
	return (0);
}

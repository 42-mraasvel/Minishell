/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/26 20:50:41 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/01 09:25:44 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft.h"

void	ft_perror(t_errnums errnum, char *string)
{
	(void)errnum; // do something with this?
	ft_putstr("Error:\n");
	if (string == NULL)
		return ;
	ft_putstr(string);
	ft_putstr("\n");
}

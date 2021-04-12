/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/26 09:05:40 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 19:04:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_error(char *prefix, char *str)
{
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	if (prefix != NULL)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(str, STDERR_FILENO);
}

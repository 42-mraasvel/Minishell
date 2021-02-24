/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 11:17:24 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/15 12:00:15 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>

void	ft_free(int cnt, ...)
{
	va_list	start;

	va_start(start, cnt);
	while (cnt > 0)
	{
		free(va_arg(start, void*));
		cnt--;
	}
	va_end(start);
}

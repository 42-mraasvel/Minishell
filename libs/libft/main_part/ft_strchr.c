/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 11:17:45 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/01 11:24:13 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	*r;

	r = (char*)s;
	while (*r != 0 && *r != (char)c)
		r++;
	if (*r != (char)c)
		return (0);
	return (r);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 14:52:30 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/09 22:27:27 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			((unsigned char*)dest)[n] = ((const unsigned char*)src)[n];
		}
	}
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}

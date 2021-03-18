/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 10:52:25 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/18 14:56:37 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"

long long int	ft_strtoll(const char *nptr);

int	main(int argc, char **argv)
{
	long long int	num;
	char			*str;

	str = "9223372036854775807";
	num = ft_strtoll(str);
	// num = strtoll(str, NULL, 0);
	printf("%lld\n", num);
	printf("ERRNO: %d : %d\n", errno, ERANGE);
	return (0);
}

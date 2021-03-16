/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 18:56:32 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/16 19:27:00 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_echo(char **args)
{
	int	ret;

	if (args[1])
	{
		if (!ft_strncmp(args[1], "-n ", 3))
			ret = ft_putstr(args[1] + 2);
		else
		{
			ret = ft_putstr(args[1]);
			if (ret == -1)
				exit(-1);
			ret = write(1, "\n", 1);
		}
		if (ret == -1)
			exit(-1);
	}
	exit(0);
}

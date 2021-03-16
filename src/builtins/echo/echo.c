/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 18:56:32 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/16 20:00:29 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	print_args(char **args, int	newline)
{
	int	i;
	int	ret;

	if (newline)
		i = 1;
	else
		i = 2;
	while (args[i])
	{
		ret = ft_putstr(args);
		if (ret == -1)
			return (-1);
		if (args[i + 1])
		{
			ret = write(1, " ", 1);
			if (ret == -1)
				return (-1);
		}	
		i++;
	}
	if (newline)
		return (write(1, "\n", 1));
	return (0);
}

int	ft_echo(char **args)
{
	int	ret;

	if (args[1])
	{
		if (!ft_strcmp(args[1], "-n"))
			ret = print_args(args, 0);
		else
			ret = print_args(args, 1);
		if (ret == -1)
			exit(-1);
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 19:33:23 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/16 20:40:28 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_pwd(char **args)
{
	int	error;
	char *path;

	error = 0;
	if (!args[1] || !ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "--"))
	{
		path = getcwd(0, 0);
		if (path == 0)
		{
			perror("pwd: getcwd");
			exit(1);
		}
		if (ft_putstr(path) == -1)
		{
			perror("pwd: writing path");
			exit(1);
		}
	}
	else if (!ft_strncmp(args[1], "--", 2))
		error = ft_putstr("pwd: bad option: --\n");
	else if (*args[1] == '-')
		error = ft_putstr("pwd: bad option: -\n");
	else if (args[1])
		error = ft_putstr("pwd: too many arguments\n");
	if (error)
		exit(1);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 19:33:23 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/16 22:16:33 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	pwd_perror(char *str)
{
	perror(str);
	return (1);
}

int	ft_pwd(char **args)
{
	char	*path;
	int		error;

	error = 0;
	if (!args[1] || !ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "--"))
	{
		path = getcwd(0, 0);
		if (path == 0)
			exit(pwd_perror("pwd"));
		if (ft_putstr(path) == -1)
			exit(pwd_perror("pwd"));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (!ft_strncmp(args[1], "--", 2))
		error = ft_putstr("pwd: bad option: --\n");
	else if (*(args[1]) == '-')
		error = ft_putstr("pwd: bad option: -\n");
	else if (args[1])
		error = ft_putstr("pwd: too many arguments\n");
	if (error)
		exit(1);
	exit(0);
}

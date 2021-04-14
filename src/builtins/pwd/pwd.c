/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 19:33:23 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/14 13:33:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

static int	pwd_perror(char *str)
{
	perror(str);
	return (1);
}

int	ft_pwd(t_data *data, char **args)
{
	char	*path;
	int		error;

	error = 0;
	if (args == NULL)
		return (0);
	if (args[0])
	{
		path = getcwd(0, 0);
		if (path == 0)
			return (pwd_perror("pwd"));
		if (ft_putstr(path) == -1)
			return (pwd_perror("pwd"));
		write(STDOUT_FILENO, "\n", 1);
		free(path);
	}
	if (args[1] && (!ft_strncmp(args[1], "--", 2) || *(args[1]) == '-'))
		error = ft_putstr("pwd: bad option: --\n");
	if (error)
		return (1);
	(void)data;
	return (0);
}

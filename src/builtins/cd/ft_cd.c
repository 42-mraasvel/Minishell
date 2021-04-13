/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:49:32 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:45:01 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include "libft.h"
#include "structs.h"

static int	ft_cd_error(char *str, int type)
{
	ft_putstr_fd("-bash: cd: ", STDERR_FILENO);
	if (type == 1)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (type == 2)
		perror(str);
	return (1);
}

int	ft_cd(t_data *data, char **args)
{
	int		ret;
	size_t	count;
	char	*home;

	count = ft_count_strings(args);
	if (count > 2)
		return (ft_cd_error(NULL, 1));
	else if (count == 2)
		ret = chdir(args[1]);
	else
	{
		home = getenv("HOME");
		if (home != NULL)
			ret = chdir(home);
		else
			ret = 0;
	}
	if (ret == -1)
		return (ft_cd_error(args[1], 2));
	(void)data;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 08:37:10 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 15:13:36 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "structs.h"

/*
** Env without any options or
** arguments.
** Prints all env variables
** Prototype maybe like : ft_env(char **args, char **envp);
*/

int	ft_env(t_data *data, char **args)
{
	size_t	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	(void)args;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 13:19:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/19 12:08:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "structs.h"

/*
** Returns true if all digit
** and fit inside of long
*/

static t_bool	exit_isnumeric_arg(char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		arg++;
	while (ft_isdigit(*arg) || ft_isspace(*arg))
		arg++;
	if (*arg != '\0')
		return (false);
	return (true);
}

static int	exit_perror(char *first, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (type == 2)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(first, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (255);
	}
}

static int	exit_normal(char *arg)
{
	long long int	exit_status;

	errno = 0;
	exit_status = ft_strtoll(arg);
	if (errno == ERANGE)
		exit(exit_perror(arg, 2));
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit((unsigned char)exit_status);
}

int	ft_exit(t_data *data, char **args)
{
	if (args[1] == NULL)
		exit(data->exit_status);
	else if (!exit_isnumeric_arg(args[1]))
		exit(exit_perror(args[1], 2));
	else if (args[2] != NULL)
		data->exit_status = exit_perror(NULL, 1);
	else
		exit(exit_normal(args[1]));
	return (data->exit_status);
}

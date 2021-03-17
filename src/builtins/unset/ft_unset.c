/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 12:13:38 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/17 13:19:03 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "proto.h"

static int	ft_unset_error(t_data *data, char *arg, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("unset: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
		data->exit_status = 1;
	}
	else
		perror("-bash");
	return (-1);
}

static size_t	count_vars(t_data *data, char **args)
{
	size_t	i;

	i = 0;
	while (*args)
	{
		if (!isvalidvar(*args))
			ft_unset_error(data, *args, 1);
		else if (getenv(*args) != NULL)
			i++;
		args++;
	}
	return (i);
}

static t_bool	varinargs(char *var, char **args)
{
	size_t	i;

	while (*args)
	{
		i = 0;
		while (var[i] != '=')
		{
			if (var[i] != (*args)[i])
				break ;
			i++;
		}
		if (var[i] == '=' && (*args)[i] == '\0')
			return (true);
		args++;
	}
	return (false);
}

static char	**remove_vars(t_data *data, char **args)
{
	size_t	size;
	size_t	i;
	char	**new_env;

	size = ft_count_strings(data->envp) - count_vars(data, args);
	new_env = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new_env == NULL)
		return (set_err_data_null(data, malloc_error));
	i = 0;
	size = 0;
	while (data->envp[size] != NULL)
	{
		if (!varinargs(data->envp[size], args))
		{
			new_env[i] = ft_strdup(data->envp[size]);
			if (new_env[i] == NULL)
			{
				ft_free_split(new_env);
				return (set_err_data_null(data, malloc_error));
			}
			i++;
		}
		size++;
	}
	return (new_env);
}

/*
** For each arg
** 	DeleteVar(arg)
**
** 1. Check arg names
** 2. Count how many variables we should replace
** 3. Reallocate array for that many variables
** 4. Copy all variables that weren't removed
** 5. Free old envp, and replace the pointer
**
** Exit status = 0 or 1 if invalid name
*/

int	ft_unset(t_data *data, char **args)
{
	char	**new_env;

	data->exit_status = 0;
	new_env = remove_vars(data, args + 1);
	if (data->error.errnum != success)
		return (ft_unset_error(data, NULL, 2));
	ft_free_split(data->envp);
	data->envp = new_env;
	*data->envpp = data->envp;
	return (data->exit_status);
}

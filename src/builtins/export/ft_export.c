/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 13:19:37 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/19 08:42:29 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"

static int	ft_export_error(t_data *data, char *arg, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
	}
	else
	{
		perror("-bash");
	}
	data->exit_status = 1;
	return (-1);
}

/*
** Size = all env variables + new variables
*/

static size_t	get_new_size(t_data *data, char **args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (args[i] != NULL)
	{
		if (!isvalidvar_asign(args[i]))
			ft_export_error(data, args[i], 1);
		else if (ft_strchr(args[i], '=') && !varinargs(args[i], args + i + 1, '='))
			size++;
		i++;
	}
	if (size == 0)
		return (0);
	i = 0;
	while (data->envp[i] != NULL)
	{
		if (!varinargs(data->envp[i], args, '='))
			size++;
		i++;
	}
	return (size);
}

static void	abort_copy_strings(t_data *data, char **new_env)
{
	ft_free_split(new_env);
	set_err_data(data, malloc_error);
}

static void	copy_strings(t_data *data, char **new_env, char **args)
{
	size_t	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (!varinargs(data->envp[i], args, '='))
		{
			new_env[i] = ft_strdup(data->envp[i]);
			if (new_env[i] == NULL)
				return (abort_copy_strings(data, new_env));
		}
		i++;
	}
	while (*args != NULL)
	{
		if (isvalidvar_asign(*args) && ft_strchr(*args, '=') != NULL
			&& !varinargs(*args, args + 1, '='))
		{
			new_env[i] = ft_strdup(*args);
			if (new_env[i] == NULL)
				return (abort_copy_strings(data, new_env));
			i++;
		}
		args++;
	}
}

static char	**add_vars(t_data *data, char **args)
{
	size_t	size;
	char	**new_env;

	size = get_new_size(data, args);
	if (size == 0)
		return (NULL);
	new_env = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new_env == NULL)
		return (set_err_data_null(data, malloc_error));
	copy_strings(data, new_env, args);
	if (data->error.errnum != success)
		return (NULL);
	return (new_env);
}

/*
** Outcomes:
**	0. No arguments
**	1. New variables
**	2. Replace existing variables
**	3. Invalid variable names
**	4. Multiple of same var in args
**
** Process:
**	1. Count total variables for new env
**	2. Reallocate env
**	3. Copy old env variables (If the variable appears in args, copy args instead)
**	4. Copy args (Skip names without assignments)
*/

int	ft_export(t_data *data, char **args)
{
	char	**new_env;

	data->exit_status = 0;
	if (*(args + 1) == NULL)
		return (ft_env(data, args));
	new_env = add_vars(data, args + 1);
	if (new_env == NULL)
	{
		if (data->error.errnum != success)
			ft_export_error(data, NULL, 2);
		return (data->exit_status);
	}
	ft_free_split(data->envp);
	data->envp = new_env;
	(*data->envpp) = new_env;
	return (data->exit_status);
}

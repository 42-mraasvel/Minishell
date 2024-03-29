/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 08:29:27 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/06 17:28:38 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"
#include "structs.h"

t_bool	varinargs(char *var, char **args, char arg_end)
{
	size_t	i;

	if (args == NULL || *args == NULL)
		return (ft_false);
	while (*args)
	{
		i = 0;
		while (var[i] != '=' && var[i] != '\0')
		{
			if (var[i] != (*args)[i])
				break ;
			i++;
		}
		if (var[i] == '=' && (*args)[i] == arg_end)
			return (ft_true);
		args++;
	}
	return (ft_false);
}

t_bool	isvalidvar(char *var)
{
	if (!isalphascore(*var))
		return (ft_false);
	var++;
	while (*var)
	{
		if (!isalphanumscore(*var))
			return (ft_false);
		var++;
	}
	return (ft_true);
}

t_bool	isvalidvar_asign(char *arg)
{
	if (!isalphascore(*arg))
		return (ft_false);
	while (*arg && *arg != '=')
	{
		if (!isalphanumscore(*arg))
			return (ft_false);
		arg++;
	}
	return (ft_true);
}

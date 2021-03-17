/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 11:34:55 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/17 12:53:24 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "structs.h"

static void	*abort_copy_envp(char **env, size_t i)
{
	while (i > 0)
	{
		i--;
		free(env[i]);
	}
	free(env);
	return (NULL);
}

static char	**copy_envp(char **envp)
{
	char	**new_env;
	size_t	i;
	size_t	size;

	size = ft_count_strings(envp);
	new_env = (char **)malloc((size + 1) * sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (new_env[i] == NULL)
			return (abort_copy_envp(new_env, i));
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

#ifdef __APPLE__

int	get_envp(t_data *data)
{
	extern char	**environ;

	environ = copy_envp(environ);
	data->envp = environ;
	if (environ == NULL)
		return (-1);
	data->envpp = &environ;
	return (0);
}

#else

int	get_envp(t_data *data)
{
	__environ = copy_envp(__environ);
	data->envp = __environ;
	if (__environ == NULL)
		return (-1);
	data->envpp = &__environ;
	return (0);
}

#endif

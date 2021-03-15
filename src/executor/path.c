/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 10:10:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 11:33:57 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include <stdio.h> // rm

static char	**get_path_strings(t_data *data)
{
	char	**paths;
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (set_err_data_null(data, malloc_error));
	return (paths);
}

static char	*cat_path(char *path, char *name)
{
	size_t	len;
	char	*result;

	len = ft_strlen(path) + ft_strlen(name) + 1;
	result = ft_calloc((len + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, path, len + 1);
	ft_strlcat(result, "/", len + 1);
	ft_strlcat(result, name, len + 1);
	return (result);
}

/*
** 2 = File exists but cannot be accessed (replace argc)
** 1 = File doesn't exist
** 0 = File Exists and can be accessed (replace argc)
** -1 = Syscall Error
*/

static int	stat_path(t_data *data, char *pathname)
{
	struct stat	buf;

	if (stat(pathname, &buf) == 0)
		return (0);
	if (errno != ENOENT && errno != EACCES)
		return (set_err_data_int(data, malloc_error, -1));
	if (errno == EACCES)
		return (2);
	return (1);
}

static int	check_path(t_data *data, char **args, char **path, char *name)
{
	size_t	i;
	char	*pathname;
	int		ret;

	i = 0;
	while (path[i] != NULL)
	{
		pathname = cat_path(path[i], name);
		if (pathname == NULL)
			return (set_err_data_int(data, malloc_error, -1));
		ret = stat_path(data, pathname);
		if (ret == 0 || ret == 2)
		{
			free(args[0]);
			args[0] = pathname;
		}
		else
			free(pathname);
		if (ret == 0 || ret == -1)
			break ;
		i++;
	}
	if (path[i] == NULL)
		return (-1);
	return (ret);
}

/*
** Return: -1 on any error
** Error types:
**	Path doesn't exist
**	Name doesn't exist for any of the paths
**	Name exists but cannot be accessed
**	Malloc Error
*/

int	lookup_path(t_data *data, char **args, char *name)
{
	char	**path;
	int		ret;

	path = get_path_strings(data);
	if (path == NULL)
		return (-1);
	ret = 0;
	if (check_path(data, args, path, name) == -1)
		ret = -1;
	ft_free_split(path);
	return (ret);
}

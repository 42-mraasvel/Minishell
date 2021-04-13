/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 10:10:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:29:07 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"

static char	**get_path_strings(void)
{
	char	**paths;
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	paths = malloc_guard(ft_split(path, ':'));
	return (paths);
}

static char	*cat_path(char *path, char *name)
{
	size_t	len;
	char	*result;

	len = ft_strlen(path) + ft_strlen(name) + 1;
	result = malloc_guard(ft_calloc((len + 1), sizeof(char)));
	ft_strlcpy(result, path, len + 1);
	ft_strlcat(result, "/", len + 1);
	ft_strlcat(result, name, len + 1);
	return (result);
}

/*
** 2 = File exists but cannot be accessed (replace argc)
** 1 = File doesn't exist
** 0 = File Exists and can be accessed (replace argc)
*/

static int	stat_path(char *pathname)
{
	struct stat	buf;

	errno = 0;
	if (stat(pathname, &buf) == 0)
		return (0);
	if (errno == EACCES)
		return (2);
	return (1);
}

static int	check_path(char **dst, char **path, char *name)
{
	char	*pathname;
	size_t	i;
	int		ret;

	i = 0;
	while (path[i] != NULL)
	{
		pathname = cat_path(path[i], name);
		ret = stat_path(pathname);
		if (ret == 0 || ret == 2)
		{
			free(*dst);
			*dst = pathname;
		}
		else
			free(pathname);
		if (ret == 0)
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

void	search_path(t_data *data, char **dst, char *name)
{
	char	**path;

	path = get_path_strings();
	if (path == NULL)
	{
		*dst = malloc_guard(ft_strdup(name));
		return ;
	}
	if (check_path(dst, path, name) == -1)
		*dst = malloc_guard(ft_strdup(name));
	ft_free_split(path);
	(void)data;
}

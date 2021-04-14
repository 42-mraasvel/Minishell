/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_var.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 13:35:18 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:08:05 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"

/*
** Return 0 if equal
** > 0 if a > b
** < 0 if a < b
*/

static int	var_cmp(char *a, char *b)
{
	size_t	i;

	i = 0;
	while (a[i] != '=' && b[i] != '=')
	{
		if ((unsigned char)a[i] != (unsigned char)b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		if (a[i] == 0 && b[i] == 0)
			return (0);
		i++;
	}
	if (a[i] == b[i])
		return (0);
	if (a[i] == '=')
		return (-1);
	else if (b[i] == '=')
		return (1);
	return (0);
}

static void	sort_envp(char **dst, char **envp)
{
	size_t	i;
	size_t	j;
	char	*key;

	i = 0;
	dst[0] = envp[0];
	while (envp[i] != NULL)
	{
		j = i + 1;
		dst[j] = envp[j];
		key = envp[j];
		if (key == NULL)
			return ;
		while (j > 0)
		{
			if (var_cmp(dst[j - 1], key) < 0)
				break ;
			dst[j] = dst[j - 1];
			j--;
		}
		dst[j] = key;
		i++;
	}
}

static char	**sorted_envp(char **envp)
{
	char	**sorted;
	size_t	len;

	len = ft_count_strings(envp);
	sorted = ft_malloc((1 + len) * sizeof(char *));
	sort_envp(sorted, envp);
	return (sorted);
}

static void	format_value(char *val)
{
	size_t	i;

	i = 1;
	ft_putchar_fd('"', STDOUT_FILENO);
	while (val[i])
	{
		if (val[i] == '"' || val[i] == '\\')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(val[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
}

/*
** Print out all arguments in lexicographical order
**
*/

int	ft_export_print(t_data *data)
{
	size_t	i;
	size_t	j;
	char	**sorted;

	i = 0;
	sorted = sorted_envp(data->envp);
	while (sorted[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (sorted[i][j] != '=' && sorted[i][j] != '\0')
		{
			ft_putchar_fd(sorted[i][j], STDOUT_FILENO);
			j++;
		}
		if (sorted[i][j] == '=')
			format_value(sorted[i] + j);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(sorted);
	return (0);
}

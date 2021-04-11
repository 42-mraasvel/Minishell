/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flush_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 12:47:25 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 09:30:54 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "structs.h"
#include "proto.h"
#include "header.h"

void	delete_errordata(void *error)
{
	if (((t_error *)error)->err_str != NULL)
		free(((t_error *)error)->err_str);
}

static void	stat_error(char *str, t_data *data)
{
	struct stat	buf;
	int			ret;

	ret = stat(str, &buf);
	ft_putstr_fd("-bash: ", STDERR_FILENO);
	if (ret == 0 && !S_ISREG(buf.st_mode))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
	else
		perror(str);
	data->exit_status = CANNOT_EXEC;
}

static void	cmd_found_error(char *str, t_data *data)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	data->exit_status = CMD_NOT_FOUND;
}

void	flush_error(t_data *data)
{
	size_t		i;
	t_error		*err;

	i = 0;
	while (i < data->exec_errors->nmemb)
	{
		err = ((t_error *)(data->exec_errors->table)) + i;
		if (err->err_str != NULL)
		{
			if (ft_strchr(err->err_str, '/') || getenv("PATH") == NULL)
				stat_error(err->err_str, data);
			else
				cmd_found_error(err->err_str, data);
		}
		else
			perror("Error");
		i++;
	}
	vect_free(data->exec_errors, delete_errordata);
	data->exec_errors = vect_init(0, sizeof(t_error));
	if (data->exec_errors == NULL)
		set_err_data(data, malloc_error);
}

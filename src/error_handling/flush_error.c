/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flush_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 12:47:25 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 13:07:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "proto.h"

void	delete_errordata(void *error)
{
	if (((t_error*)error)->err_str != NULL)
		free(((t_error*)error)->err_str);
}

void	flush_error(t_data *data)
{
	size_t		i;
	t_error		*err;
	struct stat	buf;

	i = 0;
	while (i < data->exec_errors->nmemb)
	{
		err = ((t_error*)(data->exec_errors->table)) + i;
		if (err->err_str != NULL)
		{
			stat(err->err_str, &buf);
			perror(err->err_str);
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

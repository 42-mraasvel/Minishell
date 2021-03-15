/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 12:48:46 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 12:50:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "libft.h"
#include "structs.h"

void	*set_err_data_null(t_data *data, t_errnum errnum)
{
	data->error.errnum = errnum;
	return (NULL);
}

int	set_err_data_int(t_data *data, t_errnum errnum, int ret)
{
	data->error.errnum = errnum;
	return (ret);
}

int	set_error_vec(t_data *data, t_errnum errnum, char *str, int ret)
{
	t_error	error;

	error.errnum = errnum;
	error.err_str = ft_strdup(str);
	if (error.err_str == NULL)
		return (set_err_data_int(data, malloc_error, ret));
	if (vect_pushback(data->exec_errors, &error) == -1)
		return (set_err_data_int(data, malloc_error, ret));
	return (ret);
}

void	set_err_data(t_data *data, t_errnum errnum)
{
	data->error.errnum = errnum;
}

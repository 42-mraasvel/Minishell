/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 14:20:50 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 15:16:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_termcap.h"
#include "structs.h"

t_point	point(int x, int y)
{
	return ((t_point){.x = x, .y = y});
}

t_point	point_add(t_point a, t_point b)
{
	return ((t_point){.x = a.x + b.x, .y = a.y + b.y});
}

t_bool	buffer_is_empty(t_data *data)
{
	if (data->term.hist->ptr == NULL)
	{
		if (data->term.buffer->len == 1)
			return (ft_true);
	}
	else if (data->term.hist->ptr->edited != NULL)
	{
		if (data->term.hist->ptr->edited->len == 1)
			return (ft_true);
	}
	else if (ft_strlen(data->term.hist->ptr->str) == 0)
		return (ft_true);
	return (ft_false);
}

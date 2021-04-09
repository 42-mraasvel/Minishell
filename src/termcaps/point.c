/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 14:20:50 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 14:35:40 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcap.h"

t_point	point(int x, int y)
{
	return ((t_point){.x = x, .y = y});
}

t_point	point_sub(t_point a, t_point b)
{
	return ((t_point){.x = a.x - b.x, .y = a.y - b.y});
}

t_point	point_add(t_point a, t_point b)
{
	return ((t_point){.x = a.x + b.x, .y = a.y + b.y});
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/16 14:03:09 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/12/27 20:52:40 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include "libvect.h"

typedef struct	s_test
{
	int		x;
	int		y;
	int		z;
	double	fov;
}				t_test;

t_test	gen_test(int x, int y, int z, double fov)
{
	t_test	a;

	a.x = x;
	a.y = y;
	a.z = z;
	a.fov = fov;
	return (a);
}

int	main(void)
{
	t_vect	*vector;
	t_test	test;

	vector = vect_init(0, sizeof(t_test));
	test = gen_test(5, 5, 5, 25.0);
	vect_pushback(vector, &test);
	test = gen_test(5, 5, 2, 25.0);
	printf("%d %d %d %f\n", ((t_test*)vector->table)[0].x, ((t_test*)vector->table)[0].y, ((t_test*)vector->table)[0].z, ((t_test*)vector->table)[0].fov);
	vect_free(vector, NULL);
	return (0);
}

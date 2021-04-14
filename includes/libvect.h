/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libvect.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 16:38:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:39:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECT_H
# define LIBVECT_H

# include <stddef.h>

typedef struct s_vect
{
	void	*table;
	size_t	data_size;
	size_t	nmemb;
	size_t	size;
}				t_vect;

t_vect			*vect_init(size_t initial_size, unsigned int data_type);
int				vect_pushback(t_vect *vector, void *data);
void			vect_free(t_vect *vector, void (*del)(void*));
void			*vect_add(t_vect *vector);

#endif

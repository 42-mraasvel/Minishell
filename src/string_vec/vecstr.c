/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 16:23:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 16:47:29 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vec_string.h"
#include "libft.h"

t_vecstr	*vecstr_init(size_t initial_size)
{
	t_vecstr	*new;

	if (initial_size == 0)
		initial_size = 10;
	new = (t_vecstr *)malloc(1 * sizeof(t_vecstr));
	if (new == NULL)
		return (NULL);
	new->str = (char *)malloc(initial_size * sizeof(char));
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}
	new->str[0] = '\0';
	new->size = initial_size;
	new->len = 1;
	return (new);
}

void	vecstr_free(t_vecstr *vec)
{
	if (vec == NULL)
		return ;
	free(vec->str);
	free(vec);
}


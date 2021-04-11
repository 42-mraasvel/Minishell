/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 16:23:15 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 15:20:14 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vec_string.h"
#include "libft.h"
#include "proto.h"

void	vecstr_pop(t_vecstr *ptr)
{
	if (ptr->len == 1)
		return ;
	ptr->str[ptr->len - 2] = '\0';
	ptr->len -= 1;
}

t_vecstr	*vecstr_init_str(char *str)
{
	t_vecstr	*new;
	size_t		init_size;

	init_size = ft_strlen(str) + 1;
	new = (t_vecstr *)ft_malloc(sizeof(t_vecstr));
	new->size = init_size;
	new->len = init_size;
	new->str = malloc_guard(ft_strdup(str));
	return (new);
}

t_vecstr	*vecstr_init(size_t initial_size)
{
	t_vecstr	*new;

	if (initial_size == 0)
		initial_size = 10;
	new = (t_vecstr *)ft_malloc(1 * sizeof(t_vecstr));
	if (new == NULL)
		return (NULL);
	new->str = (char *)ft_malloc(initial_size * sizeof(char));
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

void	vecstr_clear(t_vecstr *vec)
{
	free(vec->str);
	vec->str = ft_malloc(10);
	vec->size = 10;
	vec->str[0] = '\0';
	vec->len = 1;
}

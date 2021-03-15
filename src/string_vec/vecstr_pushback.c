/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr_pushback.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 16:33:28 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 17:05:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vec_string.h"

static int	vecstr_resize(t_vecstr *vec, size_t new_size)
{
	char	*new;

	new = (char *)malloc(new_size * sizeof(char));
	if (new == NULL)
		return (-1);
	ft_memcpy(new, vec->str, vec->len);
	free(vec->str);
	vec->str = new;
	vec->size = new_size;
	return (0);
}

int	vecstr_pushback_c(t_vecstr *vec, char c)
{
	if (vec->len == vec->size)
		if (vecstr_resize(vec, vec->size * 2) == -1)
			return (-1);
	vec->str[vec->len - 1] = c;
	vec->str[vec->len] = '\0';
	vec->len++;
	return (0);
}

int	vecstr_pushback_str(t_vecstr *vec, const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (vec->len + len >= vec->size)
	{
		if (vecstr_resize(vec, vec->size * 2) == -1)
			return (-1);
	}
	ft_memcpy(vec->str + vec->len - 1, s, len + 1);
	vec->len += len;
	return (0);
}

/*
** NO error handling is done:
** user is trusted to input correct len
*/

int	vecstr_pushback_substr(t_vecstr *vec, const char *s, size_t len)
{
	while (vec->len + len >= vec->size)
	{
		if (vecstr_resize(vec, vec->size * 2) == -1)
			return (-1);
	}
	ft_memcpy(vec->str + vec->len - 1, s, len);
	vec->len += len;
	vec->str[vec->len - 1] = '\0';
	return (0);
}

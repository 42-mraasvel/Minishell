/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_string.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 15:05:34 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_STRING_H
# define VEC_STRING_H

# include <stddef.h>

/*
** Size = Total size allocated for str
** Len = strlen(str) + 1; Including null-term
*/

typedef struct s_vecstr
{
	char	*str;
	size_t	len;
	size_t	size;
}	t_vecstr;

void		vecstr_free(t_vecstr *vec);
t_vecstr	*vecstr_init(size_t initial_size);

int			vecstr_pushback_c(t_vecstr *vec, char c);
int			vecstr_pushback_str(t_vecstr *vec, const char *s);
int			vecstr_pushback_substr(t_vecstr *vec, const char *s, size_t len);
void		vecstr_pop(t_vecstr *ptr);
void		vecstr_clear(t_vecstr *vec);
t_vecstr	*vecstr_init_str(char *str);

#endif

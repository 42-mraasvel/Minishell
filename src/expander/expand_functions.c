/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 19:49:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:31:58 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "header.h"
#include "proto.h"
#include "vec_string.h"
#include "structs.h"

size_t	expand_char(t_vect *strings, t_vecstr *string, char *arg)
{
	if (vecstr_pushback_c(string, *arg) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	(void)strings;
	return (1);
}

size_t	expand_squote(t_vect *strings, t_vecstr *string, char *arg)
{
	size_t	len;

	len = ft_strchr(&arg[1], '\'') - arg - 1;
	vecstr_pushback_substr(string, &arg[1], len);
	(void)strings;
	return (len + 2);
}

size_t	expand_tilde(t_vect *strings, t_vecstr *string, char *arg)
{
	char	*var;

	var = getenv("HOME");
	if (var == NULL)
		return (expand_char(strings, string, arg));
	if (vecstr_pushback_str(string, var) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (1);
}

size_t	expand_exit_status(t_vecstr *string, char *arg)
{
	char	*num;

	num = malloc_guard(ft_itoa(*get_exit_status()));
	if (vecstr_pushback_str(string, num) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	free(num);
	(void)arg;
	return (2);
}

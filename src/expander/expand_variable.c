/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 22:28:40 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/26 08:15:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "header.h"
#include "libft.h"
#include "expander.h"
#include "proto.h"
#include "vec_string.h"
#include "structs.h"

char	*get_variable(char *arg, size_t *lenptr)
{
	size_t	len;
	char	*variable;
	char	*value;

	len = 1;
	if (!isalphascore(arg[1]))
		return (NULL);
	while (isalphanumscore(arg[len]))
		len++;
	variable = malloc_guard(ft_substr(&arg[1], 0, len - 1));
	value = getenv(variable);
	free(variable);
	if (lenptr != NULL)
		*lenptr = len;
	return (value);
}

static void	pushback_and_resize(t_vect *strings, t_vecstr *string)
{
	if (vect_pushback(strings, &string->str) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	string->str = ft_calloc(10, sizeof(char));
	string->len = 1;
	string->size = 10;
}

static void	retokenize(t_vect *strings, t_vecstr *string, char *value)
{
	size_t	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (ft_isspace(value[i]))
			pushback_and_resize(strings, string);
		while (ft_isspace(value[i]))
			i++;
		if (value[i] == '\0')
			break ;
		while (value[i] != '\0' && !ft_isspace(value[i]))
		{
			if (vecstr_pushback_c(string, value[i]) == -1)
				exit_perror(GENERAL_ERROR, "malloc");
			i++;
		}
	}
}

size_t	expand_variable(t_vect *strings, t_vecstr *string, char *arg)
{
	size_t	var_len;
	char	*value;
	char	**split;

	if (arg[1] == '?')
		return (expand_exit_status(string, arg));
	if (!isalphascore(arg[1]))
		return (expand_char(strings, string, arg));
	value = get_variable(arg, &var_len);
	if (value == NULL)
		return (var_len);
	retokenize(strings, string, value);
	return (var_len);
}

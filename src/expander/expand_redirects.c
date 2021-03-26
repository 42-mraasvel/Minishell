/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redirects.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/26 08:51:44 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/26 09:48:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "expander.h"
#include "proto.h"
#include "structs.h"

static void	free_string(void *ptr)
{
	free(*(void **)ptr);
}

static int	abort_iterate_redirect_list(t_vect *strings, t_token *table, size_t i)
{
	ft_error(table[i].start, "ambiguous redirect");
	vect_free(strings, free_string);
	return (-1);
}

static int	iterate_redirect_list(t_vect *strings, t_vect *redirects)
{
	t_token	*table;
	size_t	i;

	i = 0;
	table = (t_token *)redirects->table;
	while (i < redirects->nmemb)
	{
		expand_arg(strings, table[i].start);
		if (strings->nmemb != i + 1)
			return (abort_iterate_redirect_list(strings, table, i));
		i++;
	}
	return (0);
}

static void	replace_redirects(t_vect *strings, t_vect *redirects)
{
	size_t	i;
	t_token	*table;

	i = 0;
	table = (t_token *)redirects->table;
	while (i < strings->nmemb)
	{
		free(table[i].start);
		table[i].start = ((char **)strings->table)[i];
		i++;
	}
	free(strings->table);
	free(strings);
}

int	expand_redirects(t_node *node)
{
	t_vect	*strings;

	strings = malloc_guard(vect_init(0, sizeof(char *)));
	if (iterate_redirect_list(strings, node->redirects) == -1)
		return (-1);
	replace_redirects(strings, node->redirects);
	return (0);
}

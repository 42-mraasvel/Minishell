/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 19:02:42 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 18:58:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expander.h"
#include "proto.h"
#include "libft.h"
#include "vec_string.h"
#include "structs.h"

static void	replace_args(t_vect *strings, t_node *node)
{
	char	**table;
	char	**new_args;
	size_t	i;

	table = (char **)strings->table;
	new_args = ft_malloc((strings->nmemb + 1) * sizeof(char *));
	new_args[strings->nmemb] = NULL;
	i = 0;
	while (i < strings->nmemb)
	{
		new_args[i] = table[i];
		i++;
	}
	ft_free_split(node->args);
	node->args = new_args;
	vect_free(strings, NULL);
}

t_expander	get_expander(char c)
{
	static t_expander	expanders[255] = {
		['~'] = expand_tilde,
		['$'] = expand_variable,
		['\''] = expand_squote,
		['"'] = expand_dquote
	};

	if (expanders[c] == NULL)
		return (expand_char);
	return (expanders[c]);
}

void	expand_arg(t_vect *strings, char *arg)
{
	t_vecstr	*string;
	t_expander	fnc;

	string = malloc_guard(vecstr_init(0));
	while (*arg != '\0')
	{
		fnc = get_expander(*arg);
		arg += fnc(strings, string, arg);
	}
	if (string->len == 1)
		free(string->str);
	else
		vect_pushback(strings, &string->str);
	free(string);
}

int	expand_args(t_node *node)
{
	t_vect	*strings;
	size_t	i;

	strings = malloc_guard(vect_init(0, sizeof(char *)));
	i = 0;
	while (node->args[i] != NULL)
	{
		expand_arg(strings, node->args[i]);
		i++;
	}
	replace_args(strings, node);
	return (0);
}

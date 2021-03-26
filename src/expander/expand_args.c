/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 19:02:42 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/26 09:50:10 by mraasvel      ########   odam.nl         */
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

void	expand_arg(t_vect *strings, char *arg)
{
	t_vecstr	*string;

	string = malloc_guard(vecstr_init(0));
	while (*arg != '\0')
	{
		switch(*arg) { // turn into function pointer array
			case('~'):
				arg += expand_tilde(strings, string, arg);
				break;
			case('$'):
				arg += expand_variable(strings, string, arg);
				break;
			case('\''):
				arg += expand_squote(strings, string, arg);
				break;
			case('"'):
				arg += expand_dquote(strings, string, arg);
				break;
			default:
				arg += expand_char(strings, string, arg);
				break;
		}
	}
	if (string->len == 1)
		free(string->str);
	else
		vect_pushback(strings, &string->str);
	free(string);
}

t_vect	*expand_parameters(char **args)
{
	t_vect	*strings;

	strings = malloc_guard(vect_init(0, sizeof(char *)));
	while (*args != NULL)
	{
		expand_arg(strings, *args);
		args++;
	}
	return (strings);
}

int	expand_args(t_node *node)
{
	t_vect	*strings;

	strings = expand_parameters(node->args); //! merge expand_params and expand_args
	replace_args(strings, node);
	return (0);
}

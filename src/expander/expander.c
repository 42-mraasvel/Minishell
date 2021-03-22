/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 13:29:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/22 11:26:08 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "libft.h"
#include "vec_string.h"
#include "structs.h"
#include "proto.h"

static int	abort_expander(t_token *table, size_t i)
{
	while (i > 0)
	{
		i--;
		free(table[i].start);
	}
	return (-1);
}

/*
** Expand all WORD types in TOKENS
**
** Supported Expansions:
** 	Environment variables
** 	$? $<ENV>
** Unsupported:
**	${<ENV>}
**	Non-export variables
*/

static void	allocate_operator(t_data *data, t_token *token)
{
	token->start = ft_substr(token->start, 0, token->length);
	if (token->start == NULL)
		data->error.errnum = malloc_error;
}

/*
** 1. For each token
** 2. If word
** 3. Expand variables
** 4. Else
** 5. ignore
*/

int	expander(t_data *data)
{
	size_t	i;
	t_token	*table;

	i = 0;
	table = (t_token *)data->tokens->table;
	while (i < data->tokens->nmemb)
	{
		if (table[i].type == word)
			expand_word(data, &table[i]);
		else
			allocate_operator(data, &table[i]);
		if (data->error.errnum != success)
			return (abort_expander(table, i));
		i++;
	}
	return (0);
}

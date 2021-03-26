/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_tokens.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 13:13:35 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/24 13:16:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "proto.h"
#include "lexer.h"
#include "structs.h"

int	allocate_tokens(t_data *data)
{
	t_token	*tokens;
	size_t	i;

	tokens = data->tokens->table;
	i = 0;
	while (i < data->tokens->nmemb)
	{
		tokens[i].start = malloc_guard(
				ft_substr(tokens[i].start, 0, tokens[i].length));
		i++;
	}
	return (0);
}

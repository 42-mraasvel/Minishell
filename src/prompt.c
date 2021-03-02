/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/01 23:34:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "proto.h"
#include "libvect.h"
#include "lexer.h"

int	prompt(void)
{
	int		ret;
	char	*line;
	t_vect	*tokens;

	ret = 1;
	while (ret > 0)
	{
		ft_putstr(MINISHELL_PROMPT);
		ret = ft_getline(0, &line);
		if (ret < 0)
			exit_program(error, "Getline error");
		tokens = lexer(line);
		free(line);
	}
	vect_free(tokens, NULL);
	return (success);
}

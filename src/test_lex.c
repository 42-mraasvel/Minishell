/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_lex.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 23:24:47 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/02 23:36:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"

char	*skipspace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

/*
<metacharacter>	::=	::=	'|'
					|	'<'
					|	'>'
					|	';'
					|	<blank>
					|	'\n' (newline)
				NOT IN SUBJECT:
					|	'&'
					|	'('
					|	')'

*/

t_bool	ismeta(char c)
{
	static const char	*meta = "|<>; \t\n&()";

	if (ft_strchr(meta, c) == NULL)
		return (false);
	return (true);
}

void	test_lexer(char *line)
{
	printf("Lexing: %s\n", line);
	line = skipspace(line);
	if (*line == '\0')
		return ;
	parse_command(line);
}

void	test_lex()
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		ft_putstr(MINISHELL_PROMPT);
		ret = ft_getline(0, &line);
		if (ret < 0)
			exit_program(error, "Getline error");
		test_lexer(line);
		free(line);
	}
}
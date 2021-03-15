/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 14:21:13 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "proto.h"
#include "header.h"

int	process_cli(char *line, t_data *data)
{
	data->tokens = lexer(line, data);
	if (data->tokens == NULL)
		return (0);
	print_tokens(data->tokens);
	data->root = create_tree(data->tokens);
	if (data->root == NULL)
		perror("-bash");
	if (data->root != NULL)
	{
		print_tree_depth(data->root, 0);
		executor(data->root, data);
	}
	tree_free(data->root);
	vect_free(data->tokens, NULL);
	return (0);
}

int	prompt(t_data *data)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		write(1, MINISHELL_PROMPT, sizeof(MINISHELL_PROMPT));
		ret = ft_getline(0, &line);
		if (ret < 0)
			exit_program(error, "Getline error");
		if (ret != 0)
			process_cli(line, data);
		flush_error(data);
		if (data->error.errnum != success)
			perror("Error");
		data->error.errnum = success;
		free(line);
	}
	write(1, "\n", 1);
	return (success);
}

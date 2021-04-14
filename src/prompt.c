/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:48:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "proto.h"
#include "header.h"

static void	delete_token(void *token)
{
	if (((t_token *)token)->type == operator)
		free(((t_token *)token)->start);
}

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

int	process_cli(char *line, t_data *data)
{
	data->tokens = lexer(line, data);
	if (data->tokens == NULL)
		return (0);
	allocate_tokens(data);
	if (data->error.err_str != success)
	{
		vect_free(data->tokens, NULL);
		return (-1);
	}
	data->root = create_tree(data->tokens);
	if (data->root == NULL)
		data->exit_status = GENERAL_ERROR;
	else
		executor(data->root, data);
	vect_free(data->tokens, delete_token);
	tree_free(data->root);
	return (0);
}

int	prompt(t_data *data)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
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
	return (success);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/22 11:31:36 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "proto.h"
#include "header.h"

void	delete_token(void *token)
{
	if (((t_token *)token)->type == operator)
		free(((t_token *)token)->start);
}

int	process_cli(char *line, t_data *data)
{
	data->tokens = lexer(line, data);
	if (data->tokens == NULL)
		return (0);
	expander(data);
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
	return (success);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/20 17:22:53 by mraasvel      ########   odam.nl         */
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
	if (((t_token*)token)->type == operator)
		free(((t_token*)token)->start);
}

int	process_cli(char *line, t_data *data)
{
	//! Syntax will be checked by the lexer
	data->tokens = lexer(line, data);
	if (data->tokens == NULL)
		return (0);
	// print_tokens(data->tokens);

	// printf("\nEXPANDER\n\n");
	expander(data);
	if (data->error.err_str != success)
	{
		vect_free(data->tokens, NULL);
		return (-1);
	}

	data->root = create_tree(data->tokens);
	if (data->root == NULL)
		perror("-bash");

	if (data->root != NULL)
	{
		// print_tree_depth(data->root, 0);
		executor(data->root, data);
	}

	vect_free(data->tokens, delete_token);
	// vect_free(data->tokens, NULL);
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
		write(1, "\r" MINISHELL_PROMPT, sizeof(MINISHELL_PROMPT) + 1);
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

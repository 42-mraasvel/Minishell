/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/01 09:24:14 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 23:44:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "proto.h"
#include "libvect.h"
#include "lexer.h"

int	process_cli(char *line, t_data *data)
{
	t_vect	*tokens;
	t_node	*root;

	tokens = lexer(line, data);
	if (tokens == NULL)
		return (0);
	print_tokens(tokens);
	root = create_tree(tokens);
	if (root == NULL)
		perror("-bash");
	print_tree_depth(root, 0);
	execute_tree(root);
	tree_free(root);
	vect_free(tokens, NULL);
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
		if (data->errnum != success)
			perror("Error returned from process_cli");
		free(line);
	}
	return (success);
}

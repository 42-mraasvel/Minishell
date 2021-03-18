/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/18 15:39:22 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <unistd.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include <limits.h>

void	test_execve(void);

void	end_close(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	main (void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.exec_errors = vect_init(0, sizeof(t_error));
	if (data.exec_errors == NULL)
		exit_program(malloc_error, NULL);
	data.error.errnum = success;
	if (get_envp(&data) == -1)
		exit_program(malloc_error, "OOM for env copy");
	prompt(&data);


	printf("Returning from main...\n");
	ft_free_split(data.envp);
	vect_free(data.exec_errors, NULL);
	end_close();
	return (0);
}

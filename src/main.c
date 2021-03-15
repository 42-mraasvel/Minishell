/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 20:15:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"

void	test_execve(void);

void	end_close(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

#ifdef __APPLE

char	**get_envp(void)
{
	extern char	**environ;

	return (environ);
}

#else

char	**get_envp(void)
{
	return (__environ);
}

#endif

int	main (void)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.exec_errors = vect_init(0, sizeof(t_error));
	if (data.exec_errors == NULL)
		exit_program(malloc_error, NULL);
	data.error.errnum = success;
	data.envp = get_envp();
	prompt(&data);
	vect_free(data.exec_errors, NULL);
	end_close();
	return (0);
}

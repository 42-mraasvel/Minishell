/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/13 22:34:00 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "header.h"
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include <limits.h>

void	end_close(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	*get_exit_status(void)
{
	return (&getdata()->exit_status);
}

t_data	*getdata(void)
{
	static t_data	data = {0};

	return (&data);
}

void	handle_winch(int sig)
{
	(void)sig;
	cursor_update(getdata());
}

void	ignore_signal(int sig)
{
	(void)sig;
}

int	main (void)
{
	t_data	*data;

	signal(SIGINT, ignore_signal);
	signal(SIGQUIT, ignore_signal);
	signal(SIGWINCH, handle_winch);

	data = getdata();
	ft_bzero(data, sizeof(data));
	data->exec_errors = vect_init(0, sizeof(t_error));
	if (data->exec_errors == NULL)
		exit_program(malloc_error, NULL);
	data->error.errnum = success;
	if (get_envp(data) == -1)
		exit_program(malloc_error, "OOM for env copy");
	if (isatty(STDIN_FILENO))
		prompt_termcap(data);
	else
		prompt(data);
	ft_free_split(data->envp);
	vect_free(data->exec_errors, NULL);
	// ft_putstr_fd("exit\n", STDOUT_FILENO);
	reset_term();
	end_close();
	return (data->exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/06 17:30:48 by mraasvel      ########   odam.nl         */
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

void	test_execve(void);

void	end_close(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

/*
** Should set exit status for example
*/

void	sighandler(int sig)
{
	printf("SIG: %d\n", sig);
	// ft_putstr_fd("\n" "\r" MINISHELL_PROMPT, STDOUT_FILENO);
}

void	replace_stdin() // Testing function
{
	int fd = open("command.txt", O_RDONLY);
	if (fd == -1)
		exit_perror(GENERAL_ERROR, "open");
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_perror(GENERAL_ERROR, "dup2");
	close(fd);
}

static int	*set_exit_status(t_data *data)
{
	static int	*status = NULL;

	if (status == NULL && data != NULL)
		status = &data->exit_status;
	return (status);
}

int	*get_exit_status(void)
{
	return (set_exit_status(NULL));
}

t_data	*getdata(void)
{
	static t_data	data = {0};

	return (&data);
}

int	main (void)
{
	t_data	*data;

	// signal(SIGINT, sighandler); // ctrl-C
	// signal(SIGQUIT, sighandler); // ctrl-\

	data = getdata();
	ft_bzero(data, sizeof(data));
	set_exit_status(data);
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
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	reset_term();
	end_close();
	return (data->exit_status);
}

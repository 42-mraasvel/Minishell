/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 17:58:42 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/10 13:24:53 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "header.h"
#include "proto.h"

void test_pipe()
{
	char *const	args[] = {
		"/usr/bin/cat",
		"/usr/share/dict/words",
		NULL
	};
	char *const args2[] = {
		"/usr/bin/grep",
		"-E",
		"bana",
		NULL
	};

	int		pipes[2];
	if (pipe(pipes) < 0) {
		exit_program(error, "Pipe error\n");
	}

	int pid1 = fork();
	if (pid1 < 0) {
		exit_program(error, "Fork1 error\n");
	}

	if (pid1 == 0) {
		// child1 'cat Makefile'
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		execve(args[0], args, environ);
	}


	int pid2 = fork();
	if (pid2 < 0) {
		exit_program(error, "Fork2 error\n");
	}

	if (pid2 == 0) {
		// child2 'cat'
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		execve(args2[0], args2, environ);
	}

	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/02 16:41:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "proto.h"

void test_pipe() {
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
		execve(args[0], args, __environ);
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
		execve(args2[0], args2, __environ);
	}

	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int main (void)
{
	test_pipe();
	// prompt();
	return (0);
}

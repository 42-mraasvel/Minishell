/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_execve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/14 10:12:09 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 10:35:47 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#define NOPERM "./test_exec/no_permission"
#define EXEC "./test_exec/a.out"

#ifdef __APPLE__

#else

void	test_execve(void)
{
	char *const	argv[] = {
		"lol",
		NULL
	};
	int			ret;

	ret = execve(argv[0], argv, __environ);
	perror("Execve");
	printf("Ret: %d\n", ret);
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/15 17:06:36 by mraasvel      ########   odam.nl         */
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
#include "vec_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void	test_vecstr(void)
{
	t_vecstr	*vec;
	int LEN = 10;

	srand(time(0));

	vec = vecstr_init(0);
	if (vec == NULL)
	{
		printf("String is NULL\n");
		return ;
	}
	const char *cpy = "abcde";
	for (int i = 0; i < LEN; i++) {
		printf("|%s| len |%lu| size |%lu|\n", vec->str, vec->len, vec->size);
		vecstr_pushback_substr(vec, cpy + 2, 3);
	}
	vecstr_free(vec);
}

int	main (void)
{
	t_data	data;

	test_vecstr();
	return (0);
	ft_bzero(&data, sizeof(data));
	data.exec_errors = vect_init(0, sizeof(t_error));
	if (data.exec_errors == NULL)
		exit_program(malloc_error, NULL);
	data.error.errnum = success;
	data.envp = get_envp();
	prompt(&data);
	end_close();
	return (0);
}

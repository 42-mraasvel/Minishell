/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 13:27:01 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/02/24 18:48:44 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void test() {
	chdir("~/");
	perror("Perror");
	system("ls");
}

int main (void)
{
	char	*line;
	int		ret;
	
	while (1) {
		ft_putstr("\033[1;33mmini\033[1;35mshell\033[0m$ ");
		ret = ft_getline(0, &line);
		if (ret <= 0)
			break ;
	}
	return (0);
}
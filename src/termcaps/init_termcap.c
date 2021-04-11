/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_termcap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:50:47 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 18:04:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <curses.h>
#include <stdio.h>
#include "libft.h"
#include "proto.h"
#include "structs.h"
#include "header.h"

static int	check_changes(t_data *data)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit_perror(GENERAL_ERROR, "tcgetattr");
	printf("%d - %d\n", term.c_iflag, data->term.settings.c_iflag);
	printf("%d - %d\n", term.c_lflag, data->term.settings.c_lflag);
	printf("%d - %d\n", term.c_cc[VMIN], data->term.settings.c_cc[VMIN]);
	printf("%d - %d\n", term.c_cc[VTIME], data->term.settings.c_cc[VTIME]);
	if (ft_memcmp(&term, &data->term.settings, sizeof(struct termios)) != 0)
		return (error);
	return (success);
}

/*
** https://man7.org/linux/man-pages/man3/termios.3.html
** Copied comment from reins_termcap by tbruinem
**	IMAXBEL			-	kinda useless
**	ECHO | ICANON	-	turn off canonical mode and echo
**	VMIN			-	minimal amount of characters for non-canonical read (syscall)
**	VTIME			-	minimal time-out for non-canonical read (syscall)
** Setting BAUD rate to standard: for tputs padding etc
**	ISIG			-	Turn off INTR, QUIT, SUSP, or DSUSP: generate the string instead
*/
int	ft_setterm(t_data *data, int reset)
{
	if (!reset)
	{
		if (tcgetattr(STDIN_FILENO, &data->term.original) == -1)
			exit_perror(GENERAL_ERROR, "tcgetattr");
	}
	data->term.settings = data->term.original;
	data->term.settings.c_iflag &= ~(IMAXBEL);
	data->term.settings.c_lflag &= ~(ICANON | ECHO | ISIG);
	data->term.settings.c_cc[VMIN] = 1;
	data->term.settings.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->term.settings) == -1)
		exit_perror(GENERAL_ERROR, "tcsetattr");
	data->term.changed = ft_true;
	return (success);
}

void	restore_term(t_data *data)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->term.original) == -1)
		exit_perror(GENERAL_ERROR, "tcsetattr");
}
int	init_termcap(t_data *data)
{
	char	*termtype;

	termtype = getenv("TERM");
	if (termtype == NULL)
		exit_perror(GENERAL_ERROR, "termcap");
	if (tgetent(NULL, termtype) <= 0)
		exit_perror(GENERAL_ERROR, "tgetent");
	ft_setterm(data, 0);
	data->term.hist = init_history();
	return (success);
}

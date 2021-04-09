/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termcap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 14:01:16 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 14:52:55 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include "structs.h"
#include "proto.h"

static int	ms_putchar(int c)
{
	return ((int)write(STDOUT_FILENO, &c, 1));
}

void	termcmd(char *id, int hpos, int ypos, int nlines)
{
	char	*str;

	str = tgetstr(id, NULL);
	str = tgoto(str, hpos, ypos);
	tputs(str, nlines, &ms_putchar);
}

void	delete_char(t_data *data)
{
	if (data->term.cursor.line_length == 0)
		return ;
	termcmd("dc", data->term.cursor.pos.x, data->term.cursor.pos.y, 1);
}

void	clear_line(t_data *data)
{
	t_cursor	*cur;

	cur = &data->term.cursor;
	while (cur->line_length > 0)
	{
		cursor_move(cur, point(-1, 0));
		delete_char(data);
		cur->line_length -= 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 14:00:30 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 14:50:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // rm
#include <sys/ioctl.h>
#include "libft.h"
#include "header.h"
#include "proto.h"
#include "structs.h"

void	update_winsz(void)
{
	struct winsize	argp;
	t_data			*data;

	data = getdata();
	ioctl(STDIN_FILENO, TIOCGWINSZ, &argp);
	data->term.cursor.winsz.x = argp.ws_col;
	data->term.cursor.winsz.y = argp.ws_row;
}

static void	update_position(t_cursor *cursor, int buf, int type)
{
	if (type == 0)
		cursor->pos.y = (cursor->pos.y * 10) + (buf - '0');
	else
		cursor->pos.x = (cursor->pos.x * 10) + (buf - '0');
}

/*
** first column = 1
** first row = 1
*/

void	cursor_position(t_cursor *cursor)
{
	int		ret;
	char	buf;
	int		type;

	write(STDOUT_FILENO, DSR, sizeof(DSR));
	cursor->pos.x = 0;
	cursor->pos.y = 0;
	type = 0;
	while (1)
	{
		ret = read(STDIN_FILENO, &buf, 1);
		if (ret == -1)
			exit_perror(GENERAL_ERROR, "read");
		if (buf == 'R')
			break ;
		if (buf == ';')
			type = 1;
		if (ft_isdigit(buf))
			update_position(cursor, buf, type);
	}
}

void	print_cursor(t_cursor cursor)
{
	fprintf(stderr, "CUR: %d, %d\n", cursor.pos.x, cursor.pos.y);
	fprintf(stderr, "WIN: %d, %d\n", cursor.winsz.x, cursor.winsz.y);
}

void	cursor_update(t_data *data)
{
	cursor_position(&data->term.cursor);
	update_winsz();
}

void	cursor_move(t_cursor *cursor, t_point delta)
{
	cursor->pos = point_add(cursor->pos, delta);
	if (cursor->pos.x == 0)
	{
		cursor->pos.x = cursor->winsz.x;
		cursor->pos.y -= 1;
	}
	else if (cursor->pos.x > cursor->winsz.x)
	{
		cursor->pos.x = 1;
		if (cursor->pos.y != cursor->winsz.y)
			cursor->pos.y += 1;
		else
			return ;
	}
	termcmd("cm", cursor->pos.x - 1, cursor->pos.y - 1, 1);
}

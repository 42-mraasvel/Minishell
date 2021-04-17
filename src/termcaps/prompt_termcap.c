/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_termcap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:44:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/17 15:18:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <header.h>
#include "libft.h"
#include "structs.h"
#include "proto.h"
#include "signal.h"

int	handle_uparrow(t_data *data)
{
	char	*str;

	if (data->term.hist->ptr == data->term.hist->old)
		return (0);
	str = cycle_through(data->term.hist, 1, 0);
	if (str == NULL)
		return (0);
	clear_line(data);
	if (data->term.hist->ptr->edited != NULL)
		str = data->term.hist->ptr->edited->str;
	put_line(str, &data->term.cursor);
	return (0);
}

int	handle_downarrow(t_data *data)
{
	char	*str;

	str = cycle_through(data->term.hist, 0, 1);
	clear_line(data);
	if (str != NULL && data->term.hist->ptr->edited == NULL)
		put_line(str, &data->term.cursor);
	else if (str == NULL)
		put_line(data->term.buffer->str, &data->term.cursor);
	else if (data->term.hist->ptr->edited != NULL)
		str = data->term.hist->ptr->edited->str;
	return (0);
}

static void	interrupt_buf(t_data *data)
{
	data->exit_status = FATAL_ERROR_SIG + SIGINT;
	vecstr_clear(data->term.buffer);
	delete_edited(data->term.hist);
	data->term.cursor.line_length = 0;
	ft_putprompt("^C\n");
	cursor_update(data);
}

static void	check_buf(t_data *data, char buf[6])
{
	if (ft_isprint(buf[0]))
		pushback_char(data, buf[0]);
	else if (buf[0] == NEWLINE)
		flush_line(data);
	else if (buf[0] == ESC)
	{
		if (ft_strcmp(buf, UPARROW) == 0)
			handle_uparrow(data);
		else if (ft_strcmp(buf, DOWNARROW) == 0)
			handle_downarrow(data);
	}
	else if (buf[0] == BACKSPACE && data->term.cursor.line_length != 0)
		pop_char(data);
	else if (buf[0] == CTRL_U)
	{
		pop_line(data);
		clear_line(data);
	}
	else if (buf[0] == CTRL_C)
		interrupt_buf(data);
}

int	prompt_termcap(t_data *data)
{
	char	buf[6];
	ssize_t	ret;

	init_termcap(data);
	ft_putprompt(NULL);
	data->term.cursor.line_length = 0;
	cursor_update(data);
	data->term.buffer = vecstr_init(50);
	while (1)
	{
		ft_bzero(buf, 6);
		ret = read(STDIN_FILENO, buf, 6);
		if (ret == -1)
			exit_perror(GENERAL_ERROR, "read");
		if (buf[0] == CTRL_D && buffer_is_empty(data))
			break ;
		check_buf(data, buf);
	}
	vecstr_free(data->term.buffer);
	return (success);
}

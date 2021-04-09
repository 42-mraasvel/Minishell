/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_termcap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:44:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 17:19:46 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <header.h>
#include <stdio.h> // rm
#include "libft.h"
#include "structs.h"
#include "proto.h"

void	put_line(char *str, t_cursor *cursor)
{
	int	len;

	len = ft_strlen(str);
	ft_putstr_fd(str, STDOUT_FILENO);
	while (len > 0)
	{
		cursor_move(cursor, point(1, 0));
		cursor->line_length += 1;
		len--;
	}
}

void	print_sequence(char buf[6])
{
	for (int i = 0; i < 6; i++) {
		printf("%d ", buf[i]);
	}
	printf("\n");
}

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

static void	pushback_char(t_data *data, char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	if (data->term.hist->ptr == NULL)
		vecstr_pushback_c(data->term.buffer, c);
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			data->term.hist->ptr->edited = vecstr_init_str(data->term.hist->ptr->str);
		vecstr_pushback_c(data->term.hist->ptr->edited, c);
	}
	cursor_move(&data->term.cursor, point(1, 0));
	data->term.cursor.line_length += 1;
}

static void	pop_char(t_data *data)
{
	if (data->term.hist->ptr == NULL)
		vecstr_pop(data->term.buffer);
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			data->term.hist->ptr->edited = vecstr_init_str(data->term.hist->ptr->str);
		vecstr_pop(data->term.hist->ptr->edited);
	}
	cursor_move(&data->term.cursor, point(-1, 0));
	delete_char(data);
	data->term.cursor.line_length -= 1;
}

void	flush_line(t_data *data)
{
	char	*result;

	if (data->term.hist->ptr == NULL)
		result = data->term.buffer->str;
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			result = data->term.hist->ptr->str;
		else
			result = data->term.hist->ptr->edited->str;
	}
	write(1, "\n", 1);
	if (*result != '\0')
	{
		process_cli(result, data);
		save_newest(result, data->term.hist);
		vecstr_clear(data->term.buffer);
		delete_edited(data->term.hist);
		data->term.cursor.line_length = 0;
	}
	ft_putprompt(NULL);
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
		clear_line(data);
	// else
	// 	printf("%d\n", buf[0]);
	// else if (buf[0] == '\t')
	// 	fprintf(stderr, "LEN: %s\n", data->term.buffer->str);
	// else
		// print_sequence(buf);
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
		if (buf[0] == CTRL_D)
			break ;
		check_buf(data, buf);
	}
	vecstr_free(data->term.buffer);
	return (success);
}

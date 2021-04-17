/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flush_line.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/17 14:44:48 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/17 14:48:00 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <header.h>
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

void	pushback_char(t_data *data, char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	if (data->term.hist->ptr == NULL)
		vecstr_pushback_c(data->term.buffer, c);
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			data->term.hist->ptr->edited
				= vecstr_init_str(data->term.hist->ptr->str);
		vecstr_pushback_c(data->term.hist->ptr->edited, c);
	}
	cursor_move(&data->term.cursor, point(1, 0));
	data->term.cursor.line_length += 1;
}

void	pop_char(t_data *data)
{
	if (data->term.hist->ptr == NULL)
		vecstr_pop(data->term.buffer);
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			data->term.hist->ptr->edited
				= vecstr_init_str(data->term.hist->ptr->str);
		vecstr_pop(data->term.hist->ptr->edited);
	}
	cursor_move(&data->term.cursor, point(-1, 0));
	delete_char(data);
	data->term.cursor.line_length -= 1;
}

void	pop_line(t_data *data)
{
	t_vecstr	*buf;

	if (data->term.hist->ptr == NULL)
		buf = data->term.buffer;
	else
	{
		if (data->term.hist->ptr->edited == NULL)
			data->term.hist->ptr->edited
				= vecstr_init_str(data->term.hist->ptr->str);
		buf = data->term.hist->ptr->edited;
	}
	while (buf->len != 1)
		vecstr_pop(buf);
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
		ft_setterm(data, ft_true);
	}
	data->interrupted = ft_false;
	vecstr_clear(data->term.buffer);
	delete_edited(data->term.hist);
	data->term.cursor.line_length = 0;
	ft_putprompt(NULL);
	cursor_update(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_termcap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 15:44:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/09 12:53:43 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <unistd.h>
#include <header.h>
#include <stdio.h> // rm
#include "libft.h"
#include "structs.h"
#include "proto.h"

int	handle_uparrow(t_data *data)
{
	cycle_through(data->term.hist, 1, 0);
}

int	handle_downarrow(t_data *data)
{
	cycle_through(data->term.hist, 0, 1);
}

static void	check_buf(t_data *data, char buf[6])
{
	if (ft_isprint(buf[0]))
	{
		//! print char + pushback buffer
		ft_putchar_fd(buf[0], STDOUT_FILENO);
		vecstr_pushback_c(data->term.buffer, buf[0]);
	}
	else if (buf[0] == NEWLINE)
	{
		if (data->term.hist->ptr == NULL)
		{
			save_newest(data->term.buffer->str, data->term.hist);
			ft_putchar_fd('\n', 1);
			ft_putstr(data->term.hist->new->str);
		}
		else
		{
			if (data->term.hist->ptr->edited == NULL)
			{
				ft_putchar_fd('\n', 1);
				ft_putstr(data->term.hist->ptr->str);
				save_newest(data->term.hist->ptr->str, data->term.hist);
			}
			else
			{
				ft_putchar_fd('\n', 1);
				ft_putstr(data->term.hist->ptr->edited);
				save_newest(data->term.hist->ptr->edited, data->term.hist);
			}
		}
		vecstr_clear(data->term.buffer);
		ft_putprompt("\n");
	}
	else if (buf[0] == ESC)
	{
		if (ft_strcmp(buf, UPARROW) == 0)
			handle_uparrow(data);
		else if (ft_strcmp(buf, DOWNARROW) == 0)
			handle_downarrow(data);
	}
	else if (buf[0] == BACKSPACE)
	{
		//! Delete character from terminal screen
		vecstr_pop(data->term.buffer);
	}
}

int	prompt_termcap(t_data *data)
{
	char	buf[6];
	ssize_t	ret;

	init_termcap(data);
	ft_putprompt(NULL);
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

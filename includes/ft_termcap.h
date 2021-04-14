/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_termcap.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/14 16:40:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERMCAP_H
# define FT_TERMCAP_H

# include <termios.h>
# include <vec_string.h>

# ifndef MAX_HISTORY
#  define MAX_HISTORY 1000
# endif

//! Add edited for history changes
//! Change char* to vector?

typedef struct s_tclist
{
	char				*str;
	t_vecstr			*edited;
	struct s_tclist		*next;
	struct s_tclist		*prev;	
}	t_tclist;

typedef struct s_tchist
{
	int			size;
	t_tclist	*old;
	t_tclist	*new;
	t_tclist	*ptr;
}	t_tchist;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_cursor
{
	t_point	pos;
	t_point	winsz;
	int		line_length;
}	t_cursor;

typedef struct s_termcap
{
	struct termios	original;
	struct termios	settings;
	int				changed;
	t_cursor		cursor;
	t_vecstr		*buffer;
	t_tchist		*hist;
}	t_termcap;

t_tchist	*init_history(void);

/* Key Codes */

# define CTRL_C 3
# define CTRL_D 4
# define CTRL_U 21
# define NEWLINE 10
# define ESC 27
# define BACKSPACE 127

# define UPARROW "\033[A"
# define DOWNARROW "\033[B"

# define DSR "\033[6n"

#endif

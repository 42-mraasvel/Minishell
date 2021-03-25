/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tel-bara <tel-bara@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 23:26:42 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/03/25 23:26:46 by tel-bara      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAX_HISTORY
# define MAX_HISTORY 1000
#endif
#include "libft.h"

typedef struct s_tclist
{
	char				*str;
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

//cycle up or down through history and return and display relevant string. If history pointer = null, return 0 and display active string buffer.
char	*cycle_through(t_tchist *hist, int up, int down)
{
	if (up)
	{
		if (hist->ptr == 0 && hist->new)
			hist->ptr == hist->new;
		else if (hist->ptr == hist->old)
			hist->ptr == hist->old;
		else if (hist->ptr)
			hist->ptr == hist->ptr->prev;
	}
	else if (down)
	{
		if (hist->ptr == hist->new)
			hist->ptr == 0;
		else if (hist->ptr)
			hist->ptr == hist->ptr->next;
	}
	if (hist->ptr)
		return (hist->ptr->str);
	else
		return (0);

}

void	delete_oldest(t_tchist *hist)
{
	t_tclist	*tmp;

	tmp = hist->old;
	hist->old = hist->old->next;
	hist->old->prev = 0;
	free(tmp->str);
	free(tmp);
}

//goal: save command line input into history whenever the user presses enter
int	save_newest(char *str, t_tchist *hist)
{
	t_tclist	*link;

	hist->ptr = 0;
	link = malloc_guard(sizeof(t_tclist));
	if (link == 0)
		return (-1);
	link->str = str;
	link->next = 0;
	if (hist->new == 0)
	{
		hist->old = link;
		hist->new = link;
		link->prev = 0;
	}
	else
	{
		hist->new->next = link;
		link->prev = hist->new;
		hist->new = link;
	}
	if (hist->size < MAX_HISTORY)
		hist->size++;
	else
		delete_oldest(hist);
	return (1);
}

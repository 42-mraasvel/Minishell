/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 23:26:42 by tel-bara      #+#    #+#                 */
/*   Updated: 2021/04/09 15:13:04 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "proto.h"
#include "libft.h"
#include "ft_termcap.h"

t_tchist	*init_history(void)
{
	t_tchist	*new;

	new = ft_malloc(sizeof(t_tchist));
	ft_bzero(new, sizeof(t_tchist));
	return (new);
}

//cycle up or down through history and return and display relevant string. If history pointer = null, return 0 and display active string buffer.
char	*cycle_through(t_tchist *hist, int up, int down)
{
	if (up)
	{
		if (hist->ptr == 0 && hist->new)
			hist->ptr = hist->new;
		else if (hist->ptr == hist->old)
			hist->ptr = hist->old;
		else if (hist->ptr)
			hist->ptr = hist->ptr->prev;
	}
	else if (down)
	{
		if (hist->ptr == hist->new)
			hist->ptr = 0;
		else if (hist->ptr)
			hist->ptr = hist->ptr->next;
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
	if (tmp->edited != NULL)
		vecstr_free(tmp->edited);
	free(tmp);
}

void	delete_edited(t_tchist *hist)
{
	t_tclist	*tmp;

	tmp = hist->old;
	while (tmp != NULL)
	{
		if (tmp->edited != NULL)
		{
			vecstr_free(tmp->edited);
			tmp->edited = NULL;
		}
		tmp = tmp->next;
	}
}

//goal: save command line input into history whenever the user presses enter
int	save_newest(char *str, t_tchist *hist)
{
	t_tclist	*link;

	hist->ptr = 0;
	link = ft_malloc(sizeof(t_tclist));
	link->str = malloc_guard(ft_strdup(str));
	link->edited = NULL;
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

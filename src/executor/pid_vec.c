/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pid_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/11 17:40:58 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/11 19:05:31 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include "header.h"
#include "structs.h"
#include "proto.h"

void	kill_processes(t_data *data, size_t i)
{
	t_process	*processes;

	processes = (t_process *)(data->processes->table);
	i++;
	while (i < data->processes->nmemb)
	{
		if (processes[i].ptype == builtin)
			kill(processes[i].pid, SIGKILL);
		i++;
	}
}

void	new_process(t_data *data, t_ptype type, int value)
{
	t_process	new;

	new.ptype = type;
	if (type == builtin)
		new.exit_status = value;
	else if (type == p_command)
		new.pid = value;
	if (data->processes == NULL)
		data->processes = malloc_guard(vect_init(0, sizeof(t_process)));
	if (vect_pushback(data->processes, &new) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
}

void	reset_processes(t_data *data)
{
	vect_free(data->processes, NULL);
	data->processes = NULL;
}

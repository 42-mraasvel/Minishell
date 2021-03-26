/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_node.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/25 09:31:03 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/26 10:09:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // rm
#include <stdlib.h>
#include "expander.h"
#include "libft.h"
#include "libvect.h"
#include "vec_string.h"
#include "proto.h"
#include "structs.h"

/* EDGE CASE:
	1. export var=""
		- $var (Nothing) = Pushback NOTHING:
			args {
				$var,
				NULL
			} ->
			args {
				NULL
			}
		- "$var" (Pushback argument if not part of larger word)
			args {
				"$var",
				NULL
			} ->
			args{
				"",
				NULL
			}
		- "a$var" (Just 'a')
			args {
				"a$var",
				NULL
			} ->
			args {
				"a",
				NULL
			}
	2. export var="a      b" ; echo > $var
	3. export var="a      b" ; echo > "$var"
*/

int	expand_node(t_node *node)
{
	expand_args(node);
	return (expand_redirects(node));
}

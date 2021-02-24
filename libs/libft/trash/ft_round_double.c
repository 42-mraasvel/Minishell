/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_round_double.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 13:23:06 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/19 22:33:31 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*put_one_at_front_of_string(char *string)
{
	char	*new_string;
	int		len;

	len = ft_strlen(string);
	new_string = (char*)malloc((len + 2) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_memcpy(new_string + 1, string, len + 1);
	free(string);
	new_string[0] = '1';
	return (new_string);
}

static char	*increment_string(char *string, int end)
{
	while (string[end] == '9')
	{
		string[end] = '0';
		if (end == 0)
			return (put_one_at_front_of_string(string));
		end--;
		if (string[end] == '.')
			end--;
	}
	string[end]++;
	return (string);
}

char		*ft_round_double(char *string, double number, int end, int pr)
{
	int	compare;

	while (number > 1 || number < -1)
		number = number / 10;
	compare = (int)(number * 10);
	if (compare < 5)
		return (string);
	if (compare != 5 || pr != 0)
		string = increment_string(string, end);
	else if (compare == 5)
	{
		if (string[end] == '9')
			string = increment_string(string, end);
		else if (string[end] % 2 == 1)
			string[end]++;
	}
	return (string);
}

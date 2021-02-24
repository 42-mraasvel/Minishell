/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extract_n_digits_from_double.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 22:15:12 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 16:55:30 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_double.h"
#include "libft.h"

char			*insert_radix_point(char *digits, int pow)
{
	char	*result;
	int		len;

	len = ft_strlen(digits);
	result = (char*)malloc((len + 2) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[len + 1] = '\0';
	if (pow <= 0 || pow > len)
		pow = 0;
	pow++;
	result[pow] = '.';
	ft_memcpy(result, digits, pow);
	ft_memcpy(result + pow + 1, digits + pow, len - pow);
	free(digits);
	return (result);
}

static double	extract_n_digits(double unit, char *digits,
				int power, unsigned int n)
{
	double	tens;
	int		result;

	tens = ft_pow(10, power);
	while (n > 0)
	{
		result = (int)(unit / tens);
		unit = unit - tens * result;
		tens /= 10;
		if (result < 0)
			result = -result;
		*digits = result + '0';
		digits++;
		n--;
	}
	return (unit);
}

/*
** If signif != 0, get significant digits only.
*/

char			*extract_n_digits_from_double(double unit,
				unsigned int n, int signif)
{
	char	*digits;
	int		power;

	power = dbl_exponent(unit);
	if (power < 0 && signif == 0)
		power = 0;
	digits = (char*)malloc((n + 1) * sizeof(char));
	if (digits == NULL)
		return (NULL);
	digits[n] = '\0';
	unit = extract_n_digits(unit, digits, power, n);
	digits = ft_round_double(digits, unit, n - 1, 0);
	return (digits);
}

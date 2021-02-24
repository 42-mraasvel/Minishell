/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putdouble_sn.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 09:47:28 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 16:53:54 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_double.h"

static int	inf_nan(t_double nbr)
{
	if (nbr.bitfield.mantissa != 0)
	{
		if (write(1, "nan", 3) == -1)
			return (-1);
		return (3);
	}
	if (nbr.bitfield.sign == 1)
		if (write(1, "-", 1) == -1)
			return (-1);
	if (write(1, "inf", 3) == -1)
		return (-1);
	return (3 + nbr.bitfield.sign);
}

static int	output_sn(char *digits, int pow, int hash)
{
	if (ft_putstr(digits) == -1)
		return (-1);
	if (hash == 1)
		if (write(1, ".", 1) == -1)
			return (-1);
	if (write(1, "e", 1) == -1)
		return (-1);
	if (pow < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		pow = -pow;
	}
	else if (write(1, "+", 1) == -1)
		return (-1);
	if (pow < 10)
		if (write(1, "0", 1) == -1)
			return (-1);
	return (ft_putll(pow, 0));
}

int			ft_putdouble_sn(double unit, int precision, int hash)
{
	t_double	nbr;
	char		*digits;
	int			pow;

	nbr.value = unit;
	if (precision < 0)
		precision = 6;
	if (precision != 0)
		hash = 0;
	if (nbr.bitfield.exponent == 2047)
		return (inf_nan(nbr));
	if (nbr.bitfield.sign == 1)
		if (write(1, "-", 1) == -1)
			return (-1);
	pow = dbl_exponent(unit);
	digits = extract_n_digits_from_double(nbr.value, precision + 1, 1);
	if (precision != 0)
		digits = insert_radix_point(digits, 0);
	if (output_sn(digits, pow, hash) == -1)
	{
		free(digits);
		return (-1);
	}
	free(digits);
	return (pow + 1 + (precision == 0 ? 0 : precision + 1));
}

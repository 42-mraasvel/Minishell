/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put_double.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/19 10:18:18 by mraasvel      #+#    #+#                 */
/*   Updated: 2020/11/21 16:54:25 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_double.h"
#include "libft.h"

static int		inf_nan(t_double nbr)
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

/*
** Extract all integers to the left of the radix point.
** Input: 123.456
** Result: put "123" in string, return: 0.456.
** pow = length of the integer (123.456 would be 3)
*/

static double	extract_integers(double number, int pow, char *string)
{
	double		tens;
	int			c;

	if (pow < 0)
	{
		*string = '0';
		return (number);
	}
	tens = ft_pow(10, pow);
	while (pow >= 0)
	{
		c = (int)(number / tens);
		number = number - c * tens;
		tens /= 10;
		if (c < 0)
			c = -c;
		c += '0';
		*string = c;
		string++;
		pow--;
	}
	return (number);
}

/*
** If the exponent > 52, there is no fractional part.
** Goal: extract precision fractionals from number.
** input number will look like: 0.1237....
** 1. Multiply by 10.
** 2. Typecast to int to seperate this number.
** 3. subtract the typecasted result from number.
** 4. Repeat step 1-3 precision times.
** Return value: remaining fraction of number, to be used for rounding.
*/

static double	extract_fraction(double number, int exponent,
				int precision, char *string)
{
	int	result;

	if (exponent - 1023 > 51)
	{
		while (precision > 0)
		{
			*string = '0';
			string++;
			precision--;
		}
	}
	while (precision > 0)
	{
		number *= 10;
		result = (int)number;
		number -= result;
		if (result < 0)
			result = -result;
		*string = result + '0';
		string++;
		precision--;
	}
	return (number);
}

/*
** Convert double to string representation.
** I chose string representation because rounding was easier.
*/

static char		*ft_dtoa(double number, int precision, int exponent)
{
	char	*string;
	int		size;
	int		pow;

	pow = dbl_exponent(number);
	if (pow <= 0)
		size = 1 + (precision > 0 ? precision + 2 : 1);
	else
		size = pow + 1 + (precision > 0 ? precision + 2 : 1);
	string = (char*)ft_calloc(size, sizeof(char));
	if (string == 0)
		return (NULL);
	number = extract_integers(number, pow, string);
	if (precision != 0)
	{
		string[size - precision - 2] = '.';
		number = extract_fraction(number, exponent, precision,
		string + size - precision - 1);
	}
	if (exponent - 1023 < 51)
		string = ft_round_double(string, number, size - 2, precision);
	return (string);
}

int				ft_put_double(double number, int precision)
{
	t_double	nbr;
	char		*string;
	int			len;

	nbr.value = number;
	if (precision < 0)
		precision = 6;
	if (nbr.bitfield.exponent == 2047)
		return (inf_nan(nbr));
	if (nbr.bitfield.sign == 1)
		if (write(1, "-", 1) == -1)
			return (-1);
	string = ft_dtoa(number, precision, nbr.bitfield.exponent);
	if (string == 0)
		return (-1);
	len = ft_strlen(string);
	if (write(1, string, len) == -1)
		len = -1;
	free(string);
	return (len);
}

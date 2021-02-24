Extra Functions:
	ft_isspace.c:
		int	ft_isspace(int c);
		Description:
			works the same as isspace function.
	ft_free.c:
		void	ft_free(int cnt, ...);
		Description:
			Frees cnt pointers.
			Warning: easy to misuse.
	ft_numlen_base.c:
		int	ft_numlen_base(long long nbr, int base);
		Description:
			Returns number of digits in base-version of signed integer 'nbr'.
			max value: long long.
	ft_unumlen_base.c:
		int	ft_unumlen_base(unsigned long long nbr, int base);
		Description:
			Returns number of digits in base-version of unsigned integer 'nbr'
			max value: unsigned long long
	ft_putnofc.c:
		ssize_t	ft_putnofc(size_t n, unsigned char c);
		Description:
			Writes 'c' n times to stdout.
	ft_putllu.c:
		int	ft_putllu(unsigned long long nbr, int precision);
		Description:
			Outputs any value that fits inside unsigned long long.
			Prints a minimum of precision chars.
			Precedes printed nbr with leading zeros if precision flag is given.
	ft_putstr_p.c:
		ssize_t	ft_putstr_p(char \*str, ssize_t precision);
		Description:
			Writes at most precision chars.
			Returns bytes written or -1 on error.
	ft_putllu_base.c:
		int	ft_putllu_base(unsigned long long nbr, int base, int precision, int upcase);
		Description:
			Writes nbr in base: uses 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ
			In lowercase if upcase == 0.
			If precision > numlen; writes (precision - numlen) leading zero's.
			Return: bytes written or -1 on failure.
	ft_get_tenth_exp.c
		int	ft_get_tenth_exp(double value);
		Description:
			Divide or multiply value by 10 until it is in the range of 1 <= |value| < 10.
			Useful for scientific notation of a number, I used it to generate floating point digits.
	ft_exponent.c
		double	ft_exponent(double x, double pow);
		Description:
			Returns x^pow.
			pow can be negative, not fractional. I have no idea what to do with fractional exponents.

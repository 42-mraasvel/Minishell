/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_arguments.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/24 14:16:51 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/24 17:21:32 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> // remove
#include "header.h"
#include "vec_string.h"
#include "libft.h"
#include "proto.h"
#include "struct.h"
#include "expander.h"

static char	**convert_to_args(t_vect *strings)
{
	char		**args;
	t_vecstr	**table;
	size_t		i;

	i = 0;
	args = ft_malloc((strings->nmemb + 1) * sizeof(char *));
	args[strings->nmemb] = NULL;
	table = ((t_vecstr **)strings->table);
	while (i < strings->nmemb)
	{
		args[i] = table[i]->str;
		i++;
	}
	return (args);
}

static size_t	get_char(t_vecstr *str, char c)
{
	if (vecstr_pushback_c(str, c) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (1);
}

static size_t	get_variable(t_vecstr *str, char *arg)
{
	size_t	len;
	char	*var[2];

	len = 1;
	if (arg[len] == '?') //! Expand exit status here!
		return (get_char(str, arg[0]));
		// return (expand_exit_status(data, result, str));
	if (!isalphascore(arg[len]))
		return (get_char(str, arg[0]));
	while (isalphanumscore(arg[len]))
		len++;
	var[0] = malloc_guard(ft_substr(arg, 1, len - 1));
	var[1] = getenv(var[0]);
	free(var[0]);
	if (var[1] == NULL)
		return (len);
	if (isquote(var[1][0]))
	{
		if (vecstr_pushback_substr(str, &var[1][1],
				ft_strlen(&var[1][1]) - 1) == -1)
			exit_perror(GENERAL_ERROR, "malloc");
	}
	else if (vecstr_pushback_str(str, var[1]) == -1)
		exit_perror(GENERAL_ERROR, "malloc");
	return (len);
}

static size_t	get_quotes(t_vecstr *str, char *arg)
{
	size_t	i;

	get_char(str, arg[0]);
	i = 1;
	while (arg[i] != '\'')
	{
		if (vecstr_pushback_c(str, arg[i]) == -1)
			exit_perror(GENERAL_ERROR, "malloc");
		if (arg[i] == '\0')
			return (i);
		i++;
	}
	i += get_char(str, arg[i]);
	return (i);
}

static t_vecstr	*expand_vars(char *arg)
{
	t_vecstr	*str;
	size_t		i;

	str = malloc_guard(vecstr_init(0));
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'')
			i += get_quotes(str, arg + i);
		else if (arg[i] == '$')
			i += get_variable(str, arg + i);
		else
			i += get_char(str, arg[i]);
	}
	return (str);
}

static size_t	skip_quotes(char *str, char c)
{
	size_t	i;

	i = 1;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static size_t	retokenize_size(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		while (str[i] != '\0' && !ft_isspace(str[i]))
		{
			if (str[i] == '"' || str[i] == '\'')
				i += skip_quotes(str + i, str[i]);
			i++;
		}
	}
	return (count);
}

static size_t	extract_word(char *start, char **result, int index)
{
	size_t	i;

	i = 0;
	while (start[i] != '\0')
	{
		if (ft_isspace(start[i]))
			break ;
		if (start[i] == '\'' || start[i] == '"')
			i += skip_quotes(start + i, start[i]);
		i++;
	}
	result[index] = malloc_guard(ft_substr(start, 0, i));
	return (i);
}

/*
** Split on unquoted whitespace
*/

static char	**retokenize(t_vecstr *str)
{
	size_t	i;
	size_t	result_index;
	char	**result;

	i = 0;
	result_index = 0;
	result = ft_calloc(retokenize_size(str->str) + 1, sizeof(char *));
	while (str->str[i] != '\0')
	{
		while (ft_isspace(str->str[i]))
			i++;
		if (str->str[i] == '\0')
			break ;
		i += extract_word(str->str + i, result, result_index);
		result_index++;
	}
	return (result);
}

static void	get_strings(t_vect *strings, char **args)
{
	t_vecstr	*str;
	char		**tokens;
	size_t		i;

	i = 0;
	while (args[i] != NULL)
	{
		//! VARIABLES are tokenized ON spaces: eeverythinig else is tokenized as normal.
		str = expand_vars(args[i]); // expands all dollar signs that are inside of double quotes or unquotes, returns t_vecstr value with all the expansions
		printf("STRING(%s)\n", str->str);
		tokens = malloc_guard(ft_split_set(str->str, " \n\t\f\v\r"));
		// tokens = retokenize(str); // split on whitespace like in the lexical analyzer
		printf("TOKENS:\n");
		for (int i = 0; tokens[i] != NULL; i++) {
			printf("%s\n", tokens[i]);
		}
		printf("\n");
		// vecstr_free(str);
		// expand_quotes(tokens, strings); // split individual tokens into their final strings, and pushback these t_vecstr into strings
		i++;
	}
}

/*
** Array of strings since the amount of arguments are unknown until we are finished
** 
**
**
*/

char	**expand_arguments(char **args)
{
	t_vect	*strings;
	char	**result;

	strings = malloc_guard(vect_init(0, sizeof(t_vecstr *)));
	get_strings(strings, args);
	return (args);
	result = convert_to_args(strings);
	vect_free(strings, free);
	return (result);
}

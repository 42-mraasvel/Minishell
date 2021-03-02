/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/02 15:28:18 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef enum e_tokentype
{
	operator,
	unquoted,
	single_quoted,
	double_quoted
	
}	t_tokentype;

typedef size_t (*t_tokenizer)(char *);

/*
** How a token/lexeme is specified
**
** char *start, points to the token start within the (line) variable read from stdin
** length specifies how long the token is.
** This is to avoid reallocating memory for tokens
**
*/

typedef struct s_token
{
	char		*start;
	size_t		length;
	t_tokentype	type;
}	t_token;

#endif

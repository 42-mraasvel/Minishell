/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/03/14 21:21:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef enum e_tokentype
{
	bad_token,
	operator,
	unquoted,
	singlequoted,
	doublequoted,
	word
}	t_tokentype;

typedef enum e_optype
{
	redirect_out,
	redirect_in,
	o_semicolon,
	o_pipe,
	redirect_append
}	t_optype;

typedef size_t	(*t_tokenizer)(char *);

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
	t_optype	optype;
	t_tokentype	type;
}	t_token;

#endif

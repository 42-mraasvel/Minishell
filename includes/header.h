/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 15:46:56 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/04/10 23:10:07 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define MINISHELL_PROMPT "\033[1;33mmraashell-miniradi\033[0m:$ "
// # define MINISHELL_PROMPT "\033[1;33mminishell$\033[0m "

# define GENERAL_ERROR 1
# define MISUSE_BUILTINS 2
# define CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define FATAL_ERROR_SIG 128
# define CTRL_C_ERR_CODE 130

#endif

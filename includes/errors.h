/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:59:46 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:59:46 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <structs.h>

/*
 * MACROS FOR ERROR MESSAGES
 */
/*
# define SYNTAX_ERROR "minishell: syntax error "
# define SYNTAX_QUOTE "`quote unclosed'"
# define S_QUOTE "`\''"
# define D_QUOTE "`\"'"
# define OPEN_QUOTE "`open quote'"
# define PIPE_ERROR "near unexpected token `|'"
# define REDIR_ERROR_APPEND "near unexpected token `>'"
# define REDIR_ERROR_DAPPEND "near unexpected token `>>'"
# define REDIR_ERROR "near unexpected token `newline'"
# define OPEN_ERROR "near unexpected token `('"
# define CLOSE_ERROR "near unexpected token `)'"
# define LINE_ERROR "line too long!"

//exit_code.c
char	*itoa_exit(t_shell *shell, char **str);
int		exit_code(int value);
void	exit_status(int status);

//exit_messages.c*/
void	exit_failure(t_shell *shell, char *function);
int		last_process(int value);/*
void	infile_failure(t_shell *shell, char *file);
void	outfile_failure(t_shell *shell, char *file);
int		is_directory(t_shell *shell, char **path);
void	exec_failure(t_shell *shell, char *cmd);

//printers.c
bool	syntax_error_msg(char *str);
void	path_message2(t_shell *shell, char **path, char *error_msg);
void	path_message(t_shell *shell, char **path, char *error_msg);
void	set_params(char **var, int *exit_var, char *error_msg, int code);
void	cmd_message(t_shell *shell, char *cmd, char *error_msg);

//printers2.c
void	print_exit(void);*/

#endif
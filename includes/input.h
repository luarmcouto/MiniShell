/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:20:30 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 15:46:04 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* This file contains all the functions that handles the input of the user
* either for validations or parsing the commands.
*/
#ifndef INPUT_H
# define INPUT_H
# include <structs.h>
# include <string.h>

/*
* MACROS FOR ERROR MESSAGES
*/
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
//check_len.c
bool	check_line_len(char *line);

//input_parenthesis.c
bool	check_parenthesis(char *str);

// input_validation.c
bool	input_validation(t_shell *shell);
bool	check_quotes(char *str);
bool	check_quotes_pos(char *str);
bool	check_pipes(char *str);
bool	check_redirs(char *str);

// input_validation_utils.c
bool	ft_isquote(char c);
int		ft_isredir(char *c);
void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote);
int		jump_quotes(char *str, int i);
bool	handle_redir_error(char *str, int *i, int redir_len);

// error_utils.c (funções de erro)
bool	syntax_error_msg(char *str);
int		exit_code(int value);
bool	ft_ismeta(char *str, int i);

#endif
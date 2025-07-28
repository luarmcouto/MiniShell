/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:50:01 by iwietzke          #+#    #+#             */
/*   Updated: 2025/07/27 17:50:01 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <structs.h>

typedef enum s_token_type
{
	WORD,
	PIPE,
	APPEND,
	OUTFILE,
	INFILE,
	HEREDOC,
	AND_IF,
	OR,
	PARENTHESIS,
}	t_token_type;

typedef enum s_token_state
{
	GENERAL,
	IN_DQUOTES,
	IN_SQUOTES,
	EXPAND,
}	t_token_state;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token_state	state;
	int				pos;
}	t_token;

// lexer.c
void			lexer(t_shell *shell, char *input);

// create_token_lst.c
void			tokenize_input(t_shell *shell, char *input);
int				handle_word_token(t_shell *shell, char *input, int i);
int				handle_redir(t_shell *shell, char *input, int i);
int				handle_pipe(t_shell *shell, char *input, int i);
int				handle_quotes(t_shell *shell, char *input, int i);

// del_token.c
void			del_token(void *content);

// set_token_pos.c
void			set_token_pos(t_list *lst);

// tokenize_utils.c
bool			in_quotes(char *input, int i);
bool			ft_ismeta(char *str, int i);
int				set_append(t_shell *sh, t_token *new_token, char *input, int i);
int				set_simple(t_shell *sh, t_token *new_token, char *input, int i);
bool			is_expandable(char *token);

// tokenize_utils2.c
int				check_balance(char *input, int i);
int				set_hered(t_shell *sh, t_token *new_token, char *input, int i);

// handlers_temp.c (placeholders temporários)
int				handle_or(t_shell *shell, char *input, int i);
int				handle_parenthesis(t_shell *shell, char *input, int i);
int				handle_andif(t_shell *shell, char *input, int i);

#endif
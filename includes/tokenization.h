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

/* ====== CORE TOKENIZATION ====== */

// lexer.c
void			lexer(t_shell *shell, char	*input);

// create_token_lst.c
void			tokenize_input(t_shell *shell, char *input);
int				handle_word_token(t_shell *shell, char *input, int i);
int				handle_quotes(t_shell *shell, char *input, int i);

// del_token.c
void			del_token(void *content);

// set_token_pos.c
void			set_token_pos(t_list *lst);

/* ====== SPECIFIC HANDLERS ====== */

// handle_redir.c
int				handle_redir(t_shell *shell, char *input, int i);
int				set_append(t_shell *shell, t_token *new_token, char *input, int i);
int				set_heredoc(t_shell *shell, t_token *new_token, char *input, int i);
int				set_simple_redir(t_shell *shell, t_token *new_token, char *input, int i);

// handle_pipe.c
int				handle_pipe(t_shell *shell, char *input, int i);
bool			is_valid_pipe_context(t_shell *shell, char *input, int i);

// ft_joinstrs.c
int				join_strs(t_shell *shell, char **str, char *input, int i);
int				handle_quoted_str(t_shell *shell, char **str, char *input, int i);
int				handle_nonquoted_str(t_shell *shell, char **str, char *input, int i);
char			*ft_strjoin_char(char *str, char c);

// handle_parenthesis.c
int				handle_parenthesis(t_shell *shell, char *input, int i);
int				handle_closing(t_shell *shell, char *input, int i, bool valid);
bool			validate_subs(char *subs);
int				handle_opening(t_shell *shell, char *input, int i, bool valid);
int				jump_spaces(char *input, int i);

// handle_logic_operators.c (BONUS PREPARATION)
int				handle_andif(t_shell *shell, char *input, int i);
int				handle_or(t_shell *shell, char *input, int i);
int				is_logical_operator(char *input, int i);
bool			validate_logical_context(t_shell *shell, char *input, int i, int operator);

/* ====== UTILITY FUNCTIONS ====== */

// tokenize_utils.c
bool			in_quotes(char *input, int i);
int				set_simple(t_shell *shell, t_token *new_token, char *input, int i);
bool			is_expandable(char *token);
int				is_meta_operator(char *input, int i);
int				skip_whitespace(char *input, int i);
int				find_quote_end(char *input, int i);

// tokenize_utils2.c
int				check_balance(char *input, int i);
int				set_hered(t_shell *shell, t_token *new_token, char *input, int i);

/* ====== EXPANSION SYSTEM ====== */

// handle_expand.c (preparação para próximas semanas)
char			*handle_expand(t_shell *shell, char *input, int i);
int				prcs_expansion(t_shell *shell, char **str, char *input, int i);
int				expand_unquoted(t_shell *shell, char **str, char *input, int i);
int				expand_quoted(t_shell *shell, char **str, char *input, int i);
int				expand_single(t_shell *shell, char **str, char *input, int i);

// handle_expand_utils.c (preparação para próximas semanas)
char			*ft_strjoin_char(char *str, char c);
int				ft_flag(char c, int *i, bool flag);
t_token			*create_token(t_shell *shell, char *str);

#endif
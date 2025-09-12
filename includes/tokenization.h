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
# include <stdbool.h>

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
void			lexer(t_shell *shell, char *input);

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
bool			validate_redir_syntax(t_shell *shell, char *input, int i);

// handle_pipe.c
int				handle_pipe(t_shell *shell, char *input, int i);
bool			is_valid_pipe_context(t_shell *shell, char *input, int i);

// handle_andif.c
int				handle_andif(t_shell *shell, char *input, int i);

// handle_or.c
int				handle_or(t_shell *shell, char *input, int i);

// handle_parenthesis.c
int				handle_parenthesis(t_shell *shell, char *input, int i);

/* ====== EXPANSION SYSTEM ====== */

// expand_tokens.c
void			expand_tokens(t_shell *shell);

// handle_expand.c
char			*handle_expand(t_shell *shell, char *input, int i);
int				prcs_expansion(t_shell *shell, char **str, char *input, int i);
int				expand_unquoted(t_shell *shell, char **str, char *input, int i);
int				expand_quoted(t_shell *shell, char **str, char *input, int i);

// handle_expand_utils.c
char			*get_var_value(t_shell *shell, char *var_name);
char			*expand_var_name(t_shell *shell, char *input, int *i);
bool			is_valid_var_char(char c);
int				skip_var_name(char *input, int i);

/* ====== STRING MANIPULATION ====== */

// ft_joinstrs.c
int				join_strs(t_shell *shell, char **str, char *input, int i);
int				h_quoted_str(t_shell *shell, char **str, char *input, int i);
int				h_nonquoted_str(t_shell *shell, char **str, char *input, int i);

/* ====== TOKEN UTILITIES ====== */

// check_token_type.c
t_token_type	token_type(char *value);
bool			is_operator_token(t_token_type type);
bool			is_redirect_token(t_token_type type);

// tokenize_utils.c
bool			is_special_char(char c);
bool			is_quote_char(char c);
int				skip_whitespace(char *input, int i);
bool			check_token(t_list *token);

// tokenize_utils2.c
bool			is_valid_token_sequence(t_shell *shell, t_list *tokens);
void			print_syntax_error(t_shell *shell, char *token);
bool			validate_token_list(t_shell *shell, t_list *tokens);

/* ====== VALIDATION ====== */

char	*ft_strjoin_char(char *str, char c);

// token_validation.c
bool			validate_pipe_syntax(t_shell *shell, t_list *tokens);
bool			validate_redirect_syntax(t_shell *shell, t_list *tokens);
bool			validate_operator_syntax(t_shell *shell, t_list *tokens);
bool			validate_parenthesis_syntax(t_shell *shell, t_list *tokens);

/* ====== UTILITY MACROS ====== */

# define MAX_TOKEN_LENGTH 4096
# define MAX_VAR_NAME_LENGTH 256

/* ====== TOKEN TYPE CHECKS ====== */

# define IS_REDIRECT(type) ((type) == INFILE || (type) == OUTFILE || \
                        (type) == APPEND || (type) == HEREDOC)

# define IS_LOGICAL_OP(type) ((type) == AND_IF || (type) == OR)

# define IS_OPERATOR(type) (IS_REDIRECT(type) || IS_LOGICAL_OP(type) || \
                        (type) == PIPE)

#endif
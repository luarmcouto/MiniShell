#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard libraries */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

/* Readline */
# include <readline/readline.h>
# include <readline/history.h>

/* Libft */
# include "../libft/libft.h"

/* Token types for parsing */
typedef enum e_token_type
{
	TOKEN_WORD,			// comando, argumento, palavra normal
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF			// fim da linha
} t_token_type;

/* Token structure */
typedef struct s_token
{
	char			*value;		// conteúdo do token
	t_token_type	type;		// tipo do token
	struct s_token	*next;		// próximo token
} t_token;

/* Command structure */
typedef struct s_cmd
{
	char			**args;      // ex: {"ls", "-l", NULL}
	char			*path;       // caminho completo para execve
	int				infile;      // descritor de entrada (-1 se não tem)
	int				outfile;     // descritor de saída (-1 se não tem)
	struct s_cmd	*next;       // para pipelines
}	t_cmd;

/* Error handling */
#include <errno.h>
#include <sys/stat.h>

/* Exit codes */
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1
#define EXIT_MISUSE         2
#define EXIT_EXEC_FAIL      126
#define EXIT_NOT_FOUND      127
#define EXIT_INVALID_EXIT   128
#define EXIT_SIGNAL_BASE    128

/* Global variables (only ones allowed) */
extern int	g_signal_received;
extern int	g_last_exit_status;

/* Redirection functions */
int		setup_input_redirect(char *filename);
int		setup_output_redirect(char *filename, int append_mode);
int		apply_redirections(t_cmd *cmd);
int		process_redirection_token(t_cmd *cmd, char *filename, t_token_type type);

/* Error handling functions */
void	print_error(char *cmd, char *arg, char *message);
int		handle_exec_error(char *cmd, int error_code);
int		handle_redirect_error(char *filename, int error_code);
int		handle_fork_error(void);
int		handle_pipe_error(void);
int		check_command_access(char *path);
void	update_exit_status(int status);
int		get_last_exit_status(void);
void	cleanup_and_exit(t_cmd *cmds, int exit_code);

/* Parsing functions */
t_token	*tokenize(char *input);
void	free_tokens(t_token *tokens);
void	print_tokens(t_token *tokens);
t_cmd	*parse_tokens(t_token *tokens);
t_cmd	*parse_input(char *input);
int		validate_syntax(t_token *tokens);
int		process_redirection_token(t_cmd *cmd, char *filename, t_token_type type);

void	execute_commands(t_cmd *cmds, char **envp);

/* Built-ins */
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd);

/* Utils */
void	free_cmds(t_cmd *cmds);
char	*find_cmd_path(char *cmd, char **envp);
int		ft_strcmp(const char *s1, const char *s2);

/* Temporary function for testing (will be removed when parser is ready) */
t_cmd	*create_test_cmd(char *input);

#endif
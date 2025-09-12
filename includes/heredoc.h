/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:51:19 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:51:19 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <structs.h>
# include <signal.h>
# include <sys/wait.h>

// Variável global para controle de sinais
extern volatile sig_atomic_t g_signal_received;

/* ====== CORE HEREDOC FUNCTIONS ====== */

// heredoc.c
void	process_heredocs(t_shell *shell, t_exec *exec_node);
bool	setup_heredoc(t_shell *shell, t_inf *infile);
bool	read_heredoc_input(t_shell *shell, t_inf *infile, int fd, bool should_expand);
char	*generate_temp_filename(t_shell *shell, char *eof_delimiter);
bool	has_quotes(char *str);
char	*remove_quotes(char *str);

/* ====== HEREDOC EXPANSION ====== */

// heredoc_expand.c
char	*expand_heredoc_line(t_shell *shell, char *line);
int		expand_variable_in_heredoc(t_shell *shell, char **result, char *line, int i);
int		expand_braced_variable(t_shell *shell, char **result, char *line, int i);
char	*get_env_value(t_shell *shell, char *var_name);
bool	validate_heredoc_expansion(t_shell *shell, char *line);

/* ====== HEREDOC PROCESS MANAGEMENT ====== */

// heredoc_process.c
void	setup_heredoc_signals(t_shell *shell);
void	heredoc_signal_handler(int sig);
void	restore_original_signals(void);
void	process_heredoc_tree(t_shell *shell, void *root);
void	handle_heredoc_interrupt(t_shell *shell, t_exec *exec_node);
bool	validate_heredoc_syntax(t_shell *shell, t_list *tokens);
int		count_heredocs(t_exec *exec_node);
bool	heredoc_process_fork(t_shell *shell, t_inf *infile, int fd);

/* ====== UTILITY MACROS ====== */

# define HEREDOC_PROMPT "> "
# define HEREDOC_TMP_DIR "/tmp/"
# define HEREDOC_PREFIX ".minishell_heredoc_"
# define MAX_HEREDOC_SIZE 1048576  // 1MB limit

/* ====== ERROR CODES ====== */

# define HEREDOC_SUCCESS 0
# define HEREDOC_ERROR 1
# define HEREDOC_INTERRUPT 130

#endif
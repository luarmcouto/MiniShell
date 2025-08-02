/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 10:01:51 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/02 10:01:51 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <structs.h>

/* ====== EXPANSION DURING EXECUTION ====== */

// exec_expand.c - Expansão durante execução
char	**expand_argv(t_shell *shell, char **argv);
bool	contains_spaces(char *str);
int		add_split_args(t_shell *shell, char **argv, char *expanded, int start_index);
char	**resize_argv(t_shell *shell, char **argv, int new_size);
char	*expand_filename(t_shell *shell, char *filename);
char	*expand_heredoc_line(t_shell *shell, char *line);
void	free_string_array(char **array);
int		count_argv_size(t_shell *shell, char **argv);
char	**expand_single_arg(t_shell *shell, char *arg);

/* ====== EXIT CODE MANAGEMENT ====== */

// exit_code.c - Sistema de códigos de saída
int		exit_code(int value);
int		last_process(int value);
void	exit_status(int status);
char	*itoa_exit(t_shell *shell, char **str);

// Funções utilitárias para códigos específicos
void	set_exit_code_success(void);
void	set_exit_code_error(void);
void	set_exit_code_command_not_found(void);
void	set_exit_code_permission_denied(void);
void	set_exit_code_syntax_error(void);
void	set_exit_code_signal(int signal_num);

// Funções de verificação
bool	is_exit_success(void);
bool	is_exit_error(void);
char	*get_exit_code_string(t_shell *shell);
void	reset_exit_code(void);
void	handle_ctrl_c_exit_code(void);

/* ====== EXECUTION CORE (para implementação futura) ====== */

// exec_tree.c - Execução da árvore (placeholder)
// void	exec_tree(t_shell *shell, void *root);
// void	exec_pipe(t_shell *shell, t_pipe *pipe_node);
// void	*exec_node(t_shell *shell, t_exec *exec_node);

// exec_utils.c - Utilitários de execução (placeholder)
// char	*find_cmd_path(t_shell *shell, t_list *path_list, char *command);
// void	exec_free(t_shell *shell, t_exec *exec_node);

#endif
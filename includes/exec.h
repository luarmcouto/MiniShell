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
# include <binary_tree.h>
# include <builtins.h>

// Declarações das funções que estão faltando (estão implementadas em builtins_utils.c)
int		is_builtin(const char *command);
int		exec_builtin(t_shell *shell, t_exec *exec_node);

// exec_tree.c
void	start_execution(t_shell *shell, void *tree_root);
void	execute_tree(t_shell *shell, void *tree_root);
void	execute_pipe_node(t_shell *shell, t_pipe *pipe_node);
void	execute_cmd_node(t_shell *shell, t_exec *cmd_node);
void	logic_tree_exec(t_shell *shell, void *tree_root);

// Manter compatibilidade com funções existentes
void	exec_tree(t_shell *shell, void *root);
void	exec_pipe(t_shell *shell, t_pipe *pipe_node);
void	exec_node(t_shell *shell, t_exec *exec_node);
void	lexec_tree(t_shell *shell, void *root);

// exec_utils.c
char	*resolve_command_path(t_shell *shell, t_list *path_lst, char *command);
char	*find_cmd_path(t_shell *shell, t_list *path_lst, char *command);
void	cleanup_execution(t_shell *shell, t_exec *cmd_node);
void	exec_free(t_shell *shell, t_exec *cmd_node);
int		validate_command_access(t_shell *shell, char *cmd_path);
char	*build_full_path(char *directory, char *command);

// pids_utils.c
void	handle_left_process(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	handle_right_process(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	handle_pid1(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	handle_pid2(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	wait_for_processes(pid_t pid1, pid_t pid2, int *final_status);
void	setup_pipe_fds(int pipefd[]);

// exec_stubs.c - Stubs temporários (serão movidos para módulos apropriados)
void	execute_processes(t_shell *shell, void *root);
char	**expand_argv(t_shell *shell, char **argv);
void	free_expand(char **argv);
void	check_files_order(t_shell *shell, t_exec *exec_node);
void	check_wildcards(t_shell *shell, t_exec *exec_node);
void	set_fork1_signal(void);
void	set_main_signals(void);
void	handle_heredoc(t_shell *shell, void *root);
void	is_directory(t_shell *shell, char **argv);
void	exit_failure(t_shell *shell, char *function);
void	exec_failure(t_shell *shell, char *cmd_path);
void	start_execution(t_shell *shell, void *tree_root);
void	execute_tree(t_shell *shell, void *tree_root);
void	execute_pipe_node(t_shell *shell, t_pipe *pipe_node);
void	execute_cmd_node(t_shell *shell, t_exec *cmd_node);
void	logic_tree_exec(t_shell *shell, void *tree_root);

// Manter compatibilidade com funções existentes
void	exec_tree(t_shell *shell, void *root);
void	exec_pipe(t_shell *shell, t_pipe *pipe_node);
void	exec_node(t_shell *shell, t_exec *exec_node);
void	lexec_tree(t_shell *shell, void *root);

// exec_utils.c
char	*resolve_command_path(t_shell *shell, t_list *path_lst, char *command);
char	*find_cmd_path(t_shell *shell, t_list *path_lst, char *command);
void	cleanup_execution(t_shell *shell, t_exec *cmd_node);
void	exec_free(t_shell *shell, t_exec *cmd_node);
int		validate_command_access(t_shell *shell, char *cmd_path);
char	*build_full_path(char *directory, char *command);

// pids_utils.c
void	handle_left_process(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	handle_right_process(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	wait_for_processes(pid_t pid1, pid_t pid2, int *final_status);
void	setup_pipe_fds(int pipefd[]);

#endif
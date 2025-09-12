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
# include <heredoc.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>

/* ====== EXECUTION CORE ====== */

// exec_tree.c
void	lexec_tree(t_shell *shell, void *root);
void	exec_tree(t_shell *shell, void *root);
void	exec_pipe(t_shell *shell, t_pipe *pipe_node);
void	exec_node(t_shell *shell, t_exec *exec_node);  // CORRIGIDO: void em vez de void*

// exec_utils.c
char	*find_cmd_path(t_shell *shell, t_list *path_list, char *command);
void	exec_free(t_shell *shell, t_exec *exec_node);

// exec_expand.c
char	**expand_argv(t_shell *shell, char **argv);
void	free_expand(char **argv);
char	*f(t_shell *shell, char *input);

/* ====== PROCESS MANAGEMENT ====== */

// pids_utils.c
void	handle_pid1(t_shell *shell, int pipefd[], t_pipe *pipe_node);
void	handle_pid2(t_shell *shell, int pipefd[], t_pipe *pipe_node);

/* ====== REDIRECTION SYSTEM ====== */

// redirects.c (NEW - sistema completo)
void	setup_redirections(t_shell *shell, t_exec *exec_node);
void	handle_input_redirections(t_shell *shell, t_list *infiles);
void	handle_output_redirections(t_shell *shell, t_list *outfiles);
int		open_input_file(t_shell *shell, char *filename);
int		open_heredoc_file(t_shell *shell, t_inf *infile);
void	print_file_error(t_shell *shell, char *filename, char *error_msg);

// redirects_utils.c (NEW - utilitários)
char	*expand_filename(t_shell *shell, char *filename);
void	backup_std_fds(int backup_fds[3]);
void	restore_std_fds(int backup_fds[3]);
bool	validate_filename(t_shell *shell, char *filename);
bool	check_file_permissions(t_shell *shell, char *filename, int mode);
void	clean_temp_files(t_exec *exec_node);
void	count_redirections(t_exec *exec_node, int *input_count, int *output_count);

/* ====== LEGACY FUNCTIONS (compatibilidade) ====== */

// redirects.c (EXISTING - manter compatibilidade)
void	check_files_order(t_shell *shell, t_exec *exec_node);
void	handle_infiles(t_shell *shell, t_list *infiles, int pos);
void	handle_outfiles(t_shell *s, t_list *outfiles, int pos);
void	dup_file2(char *name, int fd);
void	dup_file(char *name, int fd);

/* ====== UTILITY MACROS ====== */

# define MAX_OPEN_FILES 1024
# define DEFAULT_FILE_PERMISSIONS 0644
# define BACKUP_FD_COUNT 3

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/10 08:00:00 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <structs.h>
# include <minishell.h>
# include <binary_tree.h>

typedef struct s_env_var
{
	char	*value;
	char	*content;
	bool	is_export;
	bool	printed;
}			t_env_var;

// builtins_utils.c
int			is_builtin_command(const char *cmd);
int			execute_regular_builtin(t_shell *shell_data, t_exec *cmd_node);
int			execute_shell_builtin(t_shell *shell_data, t_exec *cmd_node);
int			is_shell_builtin(t_exec *cmd_node);
int			process_builtins(t_shell *shell_data, t_exec *cmd_node);

// cd.c
int	ft_cd(t_shell *shell, t_exec *exec_node);
int			builtin_cd(t_shell *shell_data, t_exec *cmd_node);
char		*determine_cd_path(t_shell *shell_data, char *provided_arg);
int			refresh_pwd_variables(t_shell *shell_data);
int			update_new_pwd(t_shell *shell_data, char *old_dir);

// cd_utils.c
int			handle_chdir_failure(char *directory);
int			display_cd_error(char *dir_path, char *error_msg);

// echo.c
int			ft_echo(t_exec *exec_node);
int			builtin_echo(t_exec *cmd_node);
int			check_no_newline_flag(char *argument);
void		print_echo_args(char **arguments, int start_idx, int add_newline);

// env.c
char		**create_env_array(t_shell *shell_data);
t_list		*create_path_list(t_shell *shell_data, char **envp);
int			get_path_var(t_shell *shell_data, t_list **path_list, char *path, int i);
void		display_env_list(t_list *env_lst);
void		free_env_list(t_list *envp);

// env_utils.c
t_list		*create_env_list(t_shell *shell_data, char **envp);
t_env_var	*create_env_node(t_shell *shell_data, char **envp);
char		*extract_value(t_shell *shell_data, char *env_str);
char		*extract_content(t_shell *shell_data, char *env_str);
char		*get_shell_env(t_list *envp, const char *var_name);
void		print_env_lst(t_list *lst);

// env_utils_sizes.c
int			get_content_size(char *env_str);
int			get_value_size(char *env_str);

// exit.c
int			builtin_exit(t_shell *shell_data, char **arguments);
void		handle_exit_error(t_shell *shell_data, char **arguments);
int			is_number_string(char *str);
void		exit_with_args(void);
int			get_exit_code(int new_code);


// export.c
int		builtin_export(t_shell *shell_data, char **arguments);
int			export_variable(t_shell *shell_data, const char *arg_str);
char		*build_value(t_shell *shell_data, const char *arg_str, char *equal_pos);
void		modify_existing_var(t_env_var *env_variable, t_env_var *new_variable);
void		handle_append_operation(t_shell *shell_data, t_env_var *new_variable, const char *arg_str,
				char *plus_pos);

// export_utils.c
void		set_export_flag(t_shell *shell_data, const char *variable_name);
void		display_export_list(t_list *env_lst);
void		clear_printed_flags(t_list *env_lst);
t_list		*find_next_variable(t_list *env_lst);
void		display_variable(t_env_var *env_var);

// export_utils2.c
int			update_env_variable(t_shell *shell_data, const char *var_name,
								const char *var_value);
void		modify_existing_var(t_env_var *env_variable, t_env_var *new_variable);

// pwd.c
void		ft_pwd(void);
void		builtin_pwd(void);
int			validate_pwd(t_exec *cmd_node);

// unset.c
int		builtin_unset(t_shell *shell_data, char **arguments);
void		remove_first_env_node(t_shell *shell_data, t_list *current);
void		remove_env_node(t_list *previous);
int			check_first_env_node(t_shell *shell_data, const char *variable_name);
t_list		*find_previous_node(t_list *env_lst, const char *variable_name);

// unset_utils.c
int			is_valid_var_identifier(const char *str);
void		display_invalid_identifier(char *arg_str, char *cmd_str);
void		remove_environment_var(t_shell *shell_data, const char *variable_name);
int			is_exact_variable(t_env_var *env_variable, const char *variable_name);
int			unset_variable(t_shell *shell_data, const char *var_name);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:49:40 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 16:52:07 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <binary_tree.h>
# include <structs.h>

typedef struct s_env
{
	char	*value;
	char	*content;
	bool	is_export;
	bool	printed;
}			t_env;

// builtins_utils.c
int			is_builtin(const char *command);
int			exec_builtin(t_shell *shell, t_exec *exec_node);
int			exec_parent_builtin(t_shell *shell, t_exec *exec_node);
int			is_parent_builtin(t_exec *exec_node);
int			handle_builtins(t_shell *shell, t_exec *exec_node);


// cd.c
int			ft_cd(t_shell *shell, t_exec *exec_node);
char		*get_cd_path(t_shell *shell, char *arg);
int			update_pwd_vars(t_shell *shell);
int			set_new_pwd(t_shell *shell, char *old_pwd);

// cd_utils.c
int			handle_chdir_error(char *path);
int			print_cd_error(char *path, char *msg);

// echo.c
int			ft_echo(t_exec *exec_node);
int			echo_flag_n(char *arg);
void		echo_output(char **args, int idx, int newline);

// env.c
char		**env_arr(t_shell *shell);
t_list		*path_list(t_shell *shell, char **envp);
int			get_path(t_shell *shell, t_list **path_list, char *path, int i);
void		print_env_lst(t_list *lst);
void		free_env_lst(t_list *envp);

// env_utils.c
t_list		*env_list(t_shell *shell, char **envp);
t_env		*create_node_env(t_shell *shell, char **envp);
char		*get_value(t_shell *shell, char *env);
char		*get_content(t_shell *shell, char *env);
char		*sh_get_env(t_list *envp, const char *value);

// env_utils_sizes.c
int			content_size(char *env);
int			val_size(char *env);

// exit.c
void		ft_exit(t_shell *shell, t_exec *exec_node);
void		exit_error(t_shell *shell, char **arg);
int			is_numeric(char *str);
void		exit_args(void);

// export.c
void		ft_export(t_shell *shell, char **args);
int			export_var(t_shell *shell, const char *arg);
char		*create_value(t_shell *shell, const char *arg, char *equal);
void		update_existing_var(t_env *env_var, t_env *new_env);
void		handle_append(t_shell *shell, t_env *new_env, const char *arg,
				char *plus);

// export_utils.c
void		mark_isexport(t_shell *shell, const char *var_name);
void		print_export_lst(t_list *lst);
void		reset_printed(t_list *lst);
t_list		*get_next_var(t_list *lst);
void		print_var(t_env *env);

// export_utils2.c
void		upt_env_var(t_shell *shell, t_env *new_env);
void		update_existing_var(t_env *env_var, t_env *new_env);

// pwd.c
void		ft_pwd(void);
int			check_pwd(t_exec *exec_node);

// unset.c
void		ft_unset(t_shell *shell, char **args);
void		remove_first_node(t_shell *shell, t_list *curr);
void		remove_node(t_list *prev);
int			check_first_node(t_shell *shell, const char *var_name);
t_list		*find_prev_node(t_list *lst, const char *var_name);

// unset_utils.c
int			is_valid_identifier(const char *str);
void		print_invalid_identifier(char *arg, char *cmd);
void		remove_env_var(t_shell *shell, const char *var_name);
int			is_exact_var(t_env *env_var, const char *var_name);


#endif
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

// Estrutura para variáveis de ambiente
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
int			is_parent_builtin(t_exec *exec_node);
int			handle_builtins(t_shell *shell, t_exec *exec_node);

// echo.c
int			ft_echo(t_exec *exec_node);
int			echo_flag_n(char *arg);
void		echo_output(char **args, int idx, int newline);

// pwd.c
void		ft_pwd(void);
int			check_pwd(t_exec *exec_node);

// cd.c
int			ft_cd(t_shell *shell, t_exec *exec_node);
char		*get_cd_path(t_shell *shell, char *arg);

// cd_utils.c
int			print_cd_error(char *path, char *msg);
int			handle_chdir_error(char *path);
int			update_pwd_vars(t_shell *shell);
int			set_new_pwd(t_shell *shell, char *old_pwd);

// env.c
char		**env_arr(t_shell *shell);
void		free_env_lst(t_list *envp);
void		print_env_lst(t_list *lst);

// env_utils.c
t_list		*env_list(t_shell *shell, char **envp);
t_env		*create_node_env(t_shell *shell, char **envp);
char		*sh_get_env(t_list *envp, const char *value);
int			exec_parent_builtin(t_shell *shell, t_exec *exec_node);

// builtins_stubs.c (placeholders para domingo)
void		ft_export(t_shell *shell, char **args);
void		ft_unset(t_shell *shell, char **args);
void		ft_exit(t_shell *shell, t_exec *exec_node);
int			export_var(t_shell *shell, const char *arg);

#endif
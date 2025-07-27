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

# include <libft.h>
# include <structs.h>

typedef struct s_env
{
	char	*value;
	char	*content;
	bool	is_export;
	bool	printed;
}			t_env;

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

// exit_code.c
char		*itoa_exit(t_shell *shell, char **str);
int			last_process(int value);
int			exit_code(int value);
void		exit_status(int status);

// error handling
void		exit_failure(t_shell *shell, char *function);

#endif
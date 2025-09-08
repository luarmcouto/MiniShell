/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:24:30 by luarodri          #+#    #+#             */
/*   Updated: 2024/12/08 20:24:30 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**create_env_array(t_shell *shell_data)
{
	t_list	*envp_list;
	char	**env_array;
	int		i;

	envp_list = shell_data->envp;
	i = ft_lstsize(envp_list);
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		exit_failure(shell_data, "create_env_array");
	i = 0;
	while (envp_list)
	{
		env_array[i] = ft_strjoin(((t_env_var *)envp_list->content)->value,
				((t_env_var *)envp_list->content)->content);
		if (!env_array[i])
			exit_failure(shell_data, "create_env_array");
		envp_list = envp_list->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_list	*create_path_list(t_shell *shell_data, char **envp)
{
	t_list	*path_list;
	char	*path;
	int		i;

	(void)envp;
	path_list = NULL;
	path = get_shell_env(shell_data->envp, "PATH");
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		i = get_path_var(shell_data, &path_list, path, i);
	}
	return (path_list);
}

int	get_path_var(t_shell *shell_data, t_list **path_list, char *path, int i)
{
	char	*new_path;
	int		start;

	start = i;
	while (path[i] && path[i] != ':')
		i++;
	new_path = ft_substr(path, start, i - start);
	if (!new_path)
		exit_failure(shell_data, "get_path_var");
	ft_lstadd_back(path_list, ft_lstnew(new_path));
	if (path[i] == ':')
		i++;
	return (i);
}

void	display_env_list(t_list *env_lst)
{
	t_env_var	*env_variable;

	while (env_lst)
	{
		env_variable = (t_env_var *)env_lst->content;
		if (env_variable->content && ft_strchr(env_variable->value, '='))
		{
			printf("%s", env_variable->value);
			printf("%s\n", env_variable->content);
		}
		env_lst = env_lst->next;
	}
}

void	free_env_list(t_list *envp)
{
	t_list	*temp;

	while (envp)
	{
		temp = envp->next;
		free(((t_env_var *)envp->content)->value);
		free(((t_env_var *)envp->content)->content);
		free(envp->content);
		free(envp);
		envp = temp;
	}
}
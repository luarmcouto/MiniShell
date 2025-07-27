/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:13:51 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 16:32:48 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*env_list(t_shell *shell, char **envp)
{
	t_env	*content;
	int		i;

	shell->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		content = create_node_env(shell, &envp[i]);
		if (!content)
			exit_failure(shell, "env_list");
		ft_lstadd_back(&shell->envp, ft_lstnew(content));
		i++;
	}
	return (NULL);
}

t_env	*create_node_env(t_shell *shell, char **envp)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_failure(shell, "create_node_env");
	node->value = get_value(shell, *envp);
	node->content = get_content(shell, *envp);
	node->is_export = true;
	node->printed = false;
	return (node);
}

char	*get_value(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * (val_size(env) + 1));
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env, val_size(env) + 1);
	return (value);
}

char	*get_content(t_shell *shell, char *env)
{
	char	*value;

	value = malloc(sizeof(char) * (content_size(env) + 1));
	if (!value)
		exit_failure(shell, "env_value");
	ft_strlcpy(value, env + val_size(env), ft_strlen(env));
	return (value);
}

char	*sh_get_env(t_list *envp, const char *value)
{
	t_list	*current;
	t_env	*env_entry;

	current = envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		if (ft_strncmp(env_entry->value, value, ft_strlen(value)) == 0
			&& env_entry->value[ft_strlen(value)] == '=')
			return (env_entry->content);
		current = current->next;
	}
	return (NULL);
}
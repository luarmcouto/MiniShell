/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:13:51 by luarodri          #+#    #+#             */
/*   Updated: 2024/12/08 20:13:51 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*create_env_list(t_shell *shell_data, char **envp)
{
	t_env_var	*content;
	int			i;

	shell_data->envp = NULL;
	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		content = create_env_node(shell_data, &envp[i]);
		if (!content)
			exit_failure(shell_data, "create_env_list");
		ft_lstadd_back(&shell_data->envp, ft_lstnew(content));
		i++;
	}
	return (shell_data->envp);
}

t_env_var	*create_env_node(t_shell *shell_data, char **envp)
{
	t_env_var	*node;

	node = malloc(sizeof(t_env_var));
	if (!node)
		exit_failure(shell_data, "create_env_node");
	node->value = extract_value(shell_data, *envp);
	node->content = extract_content(shell_data, *envp);
	node->is_export = true;
	node->printed = false;
	return (node);
}

char	*extract_value(t_shell *shell_data, char *env_str)
{
	char	*value;

	value = malloc(sizeof(char) * (get_value_size(env_str) + 1));
	if (!value)
		exit_failure(shell_data, "extract_value");
	ft_strlcpy(value, env_str, get_value_size(env_str) + 1);
	return (value);
}

char	*extract_content(t_shell *shell_data, char *env_str)
{
	char	*content;

	content = malloc(sizeof(char) * (get_content_size(env_str) + 1));
	if (!content)
		exit_failure(shell_data, "extract_content");
	ft_strlcpy(content, env_str + get_value_size(env_str), 
		ft_strlen(env_str) - get_value_size(env_str) + 1);
	return (content);
}

char	*get_shell_env(t_list *envp, const char *value)
{
	t_list		*current;
	t_env_var	*env_entry;

	current = envp;
	while (current)
	{
		env_entry = (t_env_var *)current->content;
		if (is_exact_variable(env_entry, value))
			return (env_entry->content);
		current = current->next;
	}
	return (NULL);
}

void	print_env_lst(t_list *lst)
{
	t_env_var	*env_var;

	while (lst)
	{
		env_var = (t_env_var *)lst->content;
		if (env_var->content && ft_strchr(env_var->value, '='))
		{
			printf("%s", env_var->value);
			printf("%s\n", env_var->content);
		}
		lst = lst->next;
	}
}
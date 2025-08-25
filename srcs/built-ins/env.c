/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:24:30 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 16:56:18 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * env_arr - Converte lista de ambiente para array
 * @shell: estrutura principal do shell
 * 
 * Converte a lista ligada de variáveis de ambiente
 * em um array de strings para usar com execve.
 * 
 * Return: array de strings terminado em NULL
 */
char	**env_arr(t_shell *shell)
{
	t_list	*envp_list;
	char	**env_arr;
	int		i;

	envp_list = shell->envp;
	i = ft_lstsize(envp_list);
	env_arr = malloc(sizeof(char *) * (i + 1));
	if (!env_arr)
		exit_failure(shell, "env_arr");
	i = 0;
	while (envp_list)
	{
		env_arr[i] = ft_strjoin(((t_env *)envp_list->content)->value,
				((t_env *)envp_list->content)->content);
		if (!env_arr[i])
			exit_failure(shell, "env_arr_1");
		envp_list = envp_list->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

/**
 * print_env_lst - Imprime lista de variáveis de ambiente
 * @lst: lista de variáveis de ambiente
 * 
 * Imprime todas as variáveis de ambiente no formato NAME=value.
 */
void	print_env_lst(t_list *lst)
{
	t_env	*env_var;

	while (lst)
	{
		env_var = (t_env *)lst->content;
		if (env_var->content && ft_strchr(env_var->value, '='))
		{
			printf("%s", env_var->value);
			printf("%s\n", env_var->content);
		}
		lst = lst->next;
	}
}

/**
 * free_env_lst - Libera lista de variáveis de ambiente
 * @envp: lista de variáveis de ambiente
 * 
 * Libera completamente a lista de variáveis de ambiente,
 * incluindo todos os strings e nós.
 */
void	free_env_lst(t_list *envp)
{
	t_list	*tmp;

	while (envp)
	{
		tmp = envp->next;
		free(((t_env *)envp->content)->value);
		free(((t_env *)envp->content)->content);
		free(envp->content);
		free(envp);
		envp = tmp;
	}
}
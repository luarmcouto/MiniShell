/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:58 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/07 13:44:10 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_shlvl(t_shell shell)
{
	t_list	*tmp;
	int		value;
	char	*n_value;

	tmp = shell.envp;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->value, "SHLVL=") == 0)
		{
			value = ft_atoi(((t_env *)tmp->content)->content);
			value++;
			n_value = ft_itoa(value);
			free(((t_env *)tmp->content)->content);
			((t_env *)tmp->content)->content = n_value;
		}
		tmp = tmp->next;
	}
	shell.envp = tmp;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	check_args(argc, argv, envp);
	env_list(&shell, envp);
	update_shlvl(shell);
	terminal(&shell, envp);
	free_env_lst(shell.envp);
	return (0);
}
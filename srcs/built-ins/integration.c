/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:00 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/01 18:08:06 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Funções de compatibilidade para integrar com o sistema existente

/**
 * Mapeamento das funções novas para as existentes 
 * (para manter compatibilidade até integração completa)
 */

// Compatibilidade com sistema antigo de built-ins
int	ft_echo(t_exec *exec_node)
{
	return (builtin_echo(exec_node));
}

void	ft_pwd(void)
{
	builtin_pwd();
}

int	ft_cd(t_shell *shell, t_exec *exec_node)
{
	return (builtin_cd(shell, exec_node));
}

// Função de integração principal
int	handle_builtins(t_shell *shell, t_exec *exec_node)
{
	return (process_builtins(shell, exec_node));
}

// Função de verificação se é built-in
int	is_builtin(const char *command)
{
	return (is_builtin_command(command));
}

// Funções placeholder para não quebrar o sistema atual
int	exec_builtin(t_shell *shell, t_exec *exec_node)
{
	return (execute_regular_builtin(shell, exec_node));
}

int	exec_parent_builtin(t_shell *shell, t_exec *exec_node)
{
	return (execute_shell_builtin(shell, exec_node));
}

int	is_parent_builtin(t_exec *exec_node)
{
	return (is_shell_builtin(exec_node));
}

// Funções básicas de env (compatibilidade)
void	print_env_lst(t_list *lst)
{
	display_env_list(lst);
}

void	free_env_lst(t_list *envp)
{
	free_env_list(envp);
}

char	*sh_get_env(t_list *envp, const char *value)
{
	return (get_shell_env(envp, value));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_stubs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:16:21 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/25 21:16:21 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * ft_export - Placeholder para comando export
 */
void	ft_export(t_shell *shell, char **args)
{
	(void)shell;
	(void)args;
	ft_putendl_fd("export: command not yet implemented", 2);
}

/**
 * export_var - Placeholder para função de export individual
 * @shell: estrutura principal do shell
 * @arg: variável a ser exportada
 * 
 * Implementação placeholder que será completada no domingo.
 * Por enquanto apenas imprime mensagem informativa.
 * 
 * Return: sempre 0 (sucesso)
 */
int	export_var(t_shell *shell, const char *arg)
{
	(void)shell;
	(void)arg;
	return (0);
}

/**
 * ft_unset - Placeholder para comando unset
 * @shell: estrutura principal do shell
 * @args: argumentos do comando
 * 
 * Implementação placeholder que será feita no domingo.
 * Por enquanto apenas imprime mensagem informativa.
 */
void	ft_unset(t_shell *shell, char **args)
{
	(void)shell;
	(void)args;
	ft_putendl_fd("unset: command not yet implemented", 2);
	exit_code(1);
}

/**
 * ft_exit - Placeholder para comando exit
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução
 * 
 * Implementação placeholder que será feita no domingo.
 * Por enquanto apenas imprime mensagem e sai com código 0.
 */
void	ft_exit(t_shell *shell, t_exec *exec_node)
{
	(void)exec_node;
	ft_putendl_fd("Goodbye!", 1);
	free_env_lst(shell->envp);
	free_shell(shell);
	exit(0);
}
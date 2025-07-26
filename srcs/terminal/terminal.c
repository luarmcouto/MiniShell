/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:21:48 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 19:55:56 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	terminal(t_shell *shell, char **envp)
{
	reset_shell(shell);
	handle_signals();
	shell_input(shell);
	shell->input = readline(shell->cwd);
	
	if (shell->input && shell->input[0] != '\0')
		add_history(shell->input);
	// Validação de input - NOVA SEÇÃO
	if (shell->input && input_validation(shell))
	{
		free_shell(shell);
		terminal(shell, envp);
		return ;
	}
	
	// Condição de saída
	if (shell->input == NULL || !ft_strcmp(shell->input, "exit"))
	{
		printf("exit\n");
		free_shell(shell);
		return ;
	}
	
	// Por enquanto só imprime o que foi digitado
	printf("You typed: %s\n", shell->input);
	
	// last_process(0); // TODO: Implementar sistema de processos
	free_shell(shell);
	terminal(shell, envp);
}

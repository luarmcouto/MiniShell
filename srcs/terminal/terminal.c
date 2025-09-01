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
	
	// Validação de input
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

	// Processar entrada com lexer
	lexer(shell, shell->trim_input);

	// Construir árvore binária
	shell->root = build_tree(shell, shell->token_lst);

	// Executar a árvore
	if (shell->root)
		execute_tree(shell, shell->root);
	
	/*
	// Debug avançado dos tokens
	printf("\n🚀 === ADVANCED TOKEN ANALYSIS ===\n");
	print_tokens(shell->token_lst);
	
	// Análise específica de parênteses
	print_parenthesis_balance(shell->token_lst);
	
	// Análise da estrutura do comando
	debug_command_structure(shell->token_lst);
	
	// Análise da sequência de tokens
	analyze_token_sequence(shell->token_lst);
	
	// TODO: Implementar sistema de processos na semana 3
	// last_process(0);
	*/
	
	free_shell(shell);
	terminal(shell, envp);
}

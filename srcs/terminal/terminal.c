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

	// NOVA SEÇÃO: Processar entrada com lexer
	lexer(shell, shell->trim_input);

	// Construir árvore binária a partir dos tokens
	shell->root = build_tree(shell, shell->token_lst);

	// Por enquanto só imprime os tokens e árvore para debug
	printf("Tokens criados:\n");
	print_tokens(shell->token_lst);

	printf("\nÁrvore binária:\n");
	print_bst(shell->root, 5);

	// TODO: Implementar sistema de execução da árvore
	// exec_tree(shell, shell->root);
	
	// last_process(0); // TODO: Implementar sistema de processos
	free_shell(shell);
	terminal(shell, envp);
}

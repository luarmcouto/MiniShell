/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:58 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/06/29 19:19:27 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Variável global para sinais (única permitida)
int	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;

	printf("=== MINISHELL - TESTE DO EXECUTOR ===\n");
	printf("Comandos disponíveis para teste:\n");
	printf("- Built-ins: echo, cd, pwd, env, exit\n");
	printf("- Externos: ls, cat, grep, etc.\n");
	printf("- Digite 'exit' para sair\n\n");

	while (1)
	{
		input = readline("minishell> ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break;
		}

		if (*input)
			add_history(input);

		// Pula linhas vazias
		if (!*input)
		{
			free(input);
			continue;
		}

		// Cria comando de teste (será substituído pelo parser)
		cmd = create_test_cmd(input);
		if (cmd)
		{
			// Executa o comando
			execute_commands(cmd, envp);
			
			// Libera memória
			free_cmds(cmd);
		}
		else
		{
			printf("Erro ao processar comando\n");
		}

		free(input);
	}

	printf("Encerrando o minishell...\n");
	return (0);
}
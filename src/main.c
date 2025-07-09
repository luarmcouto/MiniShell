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

#include "minishell.h"

// Variável global para sinais (única permitida)
int	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;

	printf("=== MINISHELL - WEEK 1 - TOKENIZER + PARSER ===\n");
	printf("Funcionalidades implementadas:\n");
	printf("- Tokenização básica\n");
	printf("- Parsing de comandos simples\n");
	printf("- Validação sintática básica\n");
	printf("- Built-ins: echo, cd, pwd, env, exit\n");
	printf("- Comandos externos básicos\n");
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

		// USA O NOVO PARSER ao invés da função temporária
		cmd = parse_input(input);
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
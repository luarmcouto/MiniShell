/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:58 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/05/24 19:19:27 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;

		if (*input)
			add_history(input);

		// Aqui depois você chama seu parser -> e passa pra executor
		// Por enquanto só printa e libera
		printf("Você digitou: %s\n", input);

		// free do input obrigatório
		free(input);
	}
	printf("Encerrando o minishell...\n");
	return (0);
}
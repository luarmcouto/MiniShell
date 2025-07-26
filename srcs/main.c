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

/*
 * Start checking for the proper run of the program
 * before starts read the user input
 * using the terminal(); that runs readline();
 *
 * User should run:
 * $./minishell
 * with no extra args
 */

void	update_shlvl(t_shell shell)
{
	// TODO: Implementar update do SHLVL quando tivermos o sistema de env completo
	(void)shell;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	check_args(argc, argv, envp);
	//env_list(&shell, envp); TODO
	//update_shlvl(shell); TODO
	terminal(&shell, envp); // Loop principal do terminal
	free_env_lst(shell.envp);
	return (0);
}
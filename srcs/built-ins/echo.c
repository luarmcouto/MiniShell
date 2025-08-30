/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:44:05 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/25 20:44:05 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * echo_flag_n - Verifica se argumento é flag -n válida
 * @arg: argumento a ser verificado
 * 
 * Verifica se o argumento é uma flag -n válida.
 * Deve começar com '-' e conter apenas 'n' após o hífen.
 * 
 * Return: 1 se é flag -n válida, 0 caso contrário
 */
int	echo_flag_n(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

/**
 * echo_output - Imprime os argumentos do echo
 * @args: array de argumentos
 * @idx: índice inicial para impressão
 * @newline: se deve imprimir nova linha no final
 * 
 * Imprime todos os argumentos a partir do índice especificado,
 * separados por espaços. Se newline for true, adiciona \n no final.
 */
void	echo_output(char **args, int idx, int newline)
{
	unsigned int	i;

	i = idx;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

/**
 * ft_echo - Implementa o comando echo
 * @exec_node: nó de execução com argumentos
 * 
 * Implementa o comando echo com suporte à flag -n.
 * A flag -n suprime a nova linha no final.
 * Permite múltiplas flags -n consecutivas.
 * 
 * Return: sempre retorna 0 (sucesso)
 */
int	ft_echo(t_exec *exec_node)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	while (exec_node->argv[i] && echo_flag_n(exec_node->argv[i]))
	{
		newline = false;
		i++;
	}
	echo_output(exec_node->argv, i, newline);
	return (0);
}
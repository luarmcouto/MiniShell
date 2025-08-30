/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:44:28 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/25 20:44:28 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * ft_pwd - Implementa o comando pwd
 * 
 * Imprime o diretório de trabalho atual.
 * Usa getcwd() para obter o caminho atual.
 * Em caso de erro, imprime mensagem de erro.
 * 
 * Return: void
 */
void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("pwd error:");
	}
}

/**
 * check_pwd - Verifica argumentos do comando pwd
 * @exec_node: nó de execução com argumentos
 * 
 * pwd não aceita argumentos conforme especificação.
 * Esta função pode ser usada para validações futuras.
 * 
 * Return: 0 se válido, 1 se inválido
 */
int	check_pwd(t_exec *exec_node)
{
	(void)exec_node;
	return (0);
}
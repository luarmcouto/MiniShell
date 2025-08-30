/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:45:07 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/25 20:45:07 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * get_cd_path - Determina o caminho para o comando cd
 * @shell: estrutura principal do shell
 * @arg: argumento passado ao cd
 * 
 * Determina qual caminho usar baseado no argumento:
 * - NULL ou vazio: usa variável HOME
 * - "-": usa variável OLDPWD e imprime o caminho
 * - qualquer outro: usa o argumento diretamente
 * 
 * Return: ponteiro para o caminho ou NULL em erro
 */
char	*get_cd_path(t_shell *shell, char *arg)
{
	char	*home;
	char	*oldpwd;

	if (!arg)
	{
		home = sh_get_env(shell->envp, "HOME");
		if (!home)
			return (print_cd_error(NULL, "HOME not set"), NULL);
		return (home);
	}
	if (ft_strcmp(arg, "-") == 0)
	{
		oldpwd = sh_get_env(shell->envp, "OLDPWD");
		if (!oldpwd)
			return (print_cd_error(NULL, "OLDPWD not set"), NULL);
		ft_putendl_fd(oldpwd, 1);
		return (oldpwd);
	}
	return (arg);
}

/**
 * ft_cd - Implementa o comando cd
 * @shell: estrutura principal do shell
 * @exec_node: nó de execução com argumentos
 * 
 * Implementa mudança de diretório com validações:
 * - Aceita no máximo 2 argumentos (cd + caminho)
 * - Obtém caminho apropriado via get_cd_path
 * - Executa chdir() e atualiza variáveis PWD/OLDPWD
 * 
 * Return: 0 em sucesso, 1 em erro
 */
int	ft_cd(t_shell *shell, t_exec *exec_node)
{
	char	*path;
	int		i;

	i = 0;
	while (exec_node->argv[i])
		i++;
	if (i > 2)
		return (print_cd_error(NULL, "too many arguments"));
	path = get_cd_path(shell, exec_node->argv[1]);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (handle_chdir_error(path));
	return (update_pwd_vars(shell));
}
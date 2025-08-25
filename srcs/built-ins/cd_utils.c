/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:45:44 by iwietzke          #+#    #+#             */
/*   Updated: 2025/08/25 20:45:44 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * print_cd_error - Imprime erro do comando cd
 * @path: caminho que causou erro (pode ser NULL)
 * @msg: mensagem de erro
 * 
 * Imprime erro formatado do comando cd no stderr.
 * 
 * Return: sempre retorna 1 (código de erro)
 */
int	print_cd_error(char *path, char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}

/**
 * handle_chdir_error - Trata erros do chdir()
 * @path: caminho que causou erro
 * 
 * Analisa errno e imprime mensagem apropriada.
 * 
 * Return: sempre retorna 1 (código de erro)
 */
int	handle_chdir_error(char *path)
{
	if (errno == ENOENT)
		return (print_cd_error(path, "No such file or directory"));
	if (errno == ENOTDIR)
		return (print_cd_error(path, "Not a directory"));
	if (errno == EACCES)
		return (print_cd_error(path, "Permission denied"));
	return (print_cd_error(path, "chdir failed"));
}

/**
 * update_pwd_vars - Atualiza variáveis PWD e OLDPWD
 * @shell: estrutura principal do shell
 * 
 * Obtém PWD atual, salva como OLDPWD, obtém novo PWD
 * e atualiza ambas variáveis no ambiente.
 * 
 * Return: 0 em sucesso, 1 em erro
 */
int	update_pwd_vars(t_shell *shell)
{
	char	*old_pwd;
	char	*path;

	path = sh_get_env(shell->envp, "PWD");
	if (path)
		old_pwd = ft_strdup(path);
	else
		old_pwd = ft_strdup("");
	if (!old_pwd)
		exit_failure(shell, "cd: oldpwd allocation");
	return (set_new_pwd(shell, old_pwd));
}

/**
 * set_new_pwd - Define novas variáveis PWD e OLDPWD
 * @shell: estrutura principal do shell
 * @old_pwd: valor antigo do PWD
 * 
 * Obtém diretório atual, cria strings PWD= e OLDPWD=,
 * exporta as variáveis e libera memória.
 * 
 * Return: 0 em sucesso, 1 em erro
 */
int	set_new_pwd(t_shell *shell, char *old_pwd)
{
	char	*pwd;
	char	*pwd_var;
	char	*old_pwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(old_pwd), print_cd_error(NULL,
				"error retrieving current directory"));
	pwd_var = ft_strjoin("PWD=", pwd);
	old_pwd_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!pwd_var || !old_pwd_var)
		exit_failure(shell, "cd: var allocation");
	export_var(shell, pwd_var);
	export_var(shell, old_pwd_var);
	free(pwd);
	free(pwd_var);
	free(old_pwd);
	free(old_pwd_var);
	return (0);
}
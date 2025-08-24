/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarmcouto <luarmcouto@student.42porto.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:00:00 by luarmcouto        #+#    #+#             */
/*   Updated: 2025/08/09 11:00:00 by luarmcouto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * build_full_path - Constrói caminho completo
 * @directory: diretório base (ex: "/usr/bin")
 * @command: nome do comando (ex: "ls")
 * 
 * Combina diretório e comando para formar caminho absoluto.
 * Adiciona '/' entre diretório e comando se necessário.
 * 
 * Return: caminho completo (ex: "/usr/bin/ls") ou NULL se erro
 */
char	*build_full_path(char *directory, char *command)
{
	char	*temp_path;
	char	*full_path;

	if (!directory || !command)
		return (NULL);
	
	// Adiciona '/' ao final do diretório se não tiver
	temp_path = ft_strjoin(directory, "/");
	if (!temp_path)
		return (NULL);
	
	// Adiciona o nome do comando
	full_path = ft_strjoin(temp_path, command);
	free(temp_path);
	
	return (full_path);
}

/**
 * validate_command_access - Valida se comando é acessível
 * @shell: estrutura principal do shell
 * @cmd_path: caminho do comando para validar
 * 
 * Verifica se o arquivo existe e é executável usando access().
 * Trata casos especiais como diretórios e arquivos inexistentes.
 * 
 * Return: 1 se comando é válido e executável, 0 caso contrário
 */
int	validate_command_access(t_shell *shell, char *cmd_path)
{
	(void)shell;
	struct stat	path_stat;

	if (!cmd_path)
		return (0);
	
	// Verifica se arquivo existe
	if (access(cmd_path, F_OK) != 0)
	{
		// TODO: Implementar tratamento de erro "command not found"
		return (0);
	}
	
	// Verifica se é diretório
	if (stat(cmd_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			// TODO: Implementar erro "is a directory"
			return (0);
		}
	}
	
	// Verifica se é executável
	if (access(cmd_path, X_OK) != 0)
	{
		// TODO: Implementar erro "permission denied"
		return (0);
	}
	
	return (1);
}

/**
 * resolve_command_path - Resolve caminho completo do comando
 * @shell: estrutura principal do shell
 * @path_lst: lista de diretórios do PATH
 * @command: comando a ser localizado
 * 
 * Localiza comando no sistema:
 * 1. Se comando já é caminho absoluto/relativo (contém '/'), usa direto
 * 2. Caso contrário, procura nos diretórios do PATH
 * 3. Testa cada diretório até encontrar comando executável
 * 
 * Return: caminho completo do comando ou NULL se não encontrado
 */
char	*resolve_command_path(t_shell *shell, t_list *path_lst, char *command)
{
	(void)shell;
	t_list	*current_dir;
	char	*test_path;
	char	*final_path;

	if (!command || !*command)
		return (NULL);
	
	// Se comando já contém '/', usa caminho direto
	if (ft_strchr(command, '/'))
	{
		if (validate_command_access(shell, command))
			return (ft_strdup(command));
		return (NULL);
	}
	
	// Procura comando nos diretórios do PATH
	current_dir = path_lst;
	while (current_dir)
	{
		test_path = build_full_path((char *)current_dir->content, command);
		if (!test_path)
		{
			current_dir = current_dir->next;
			continue ;
		}
		
		if (validate_command_access(shell, test_path))
		{
			final_path = ft_strdup(test_path);
			free(test_path);
			return (final_path);
		}
		
		free(test_path);
		current_dir = current_dir->next;
	}
	
	// Comando não encontrado
	return (NULL);
}

/**
 * find_cmd_path - Compatibilidade com nome usado no projeto de referência
 * Apenas chama resolve_command_path com nome diferente
 */
char	*find_cmd_path(t_shell *shell, t_list *path_lst, char *command)
{
	return (resolve_command_path(shell, path_lst, command));
}

/**
 * cleanup_execution - Limpa recursos após execução
 * @shell: estrutura principal do shell
 * @cmd_node: nó de comando executado
 * 
 * Libera memória e recursos utilizados durante a execução:
 * - Libera argv expandido se necessário
 * - Libera caminho do comando
 * - Libera outras estruturas temporárias
 */
void	cleanup_execution(t_shell *shell, t_exec *cmd_node)
{
	(void)shell;    // Placeholder para evitar warning
	(void)cmd_node; // Placeholder para evitar warning
	
	// TODO: Implementar limpeza baseada na estrutura atual
	// Exemplos de limpeza que podem ser necessárias:
	
	// if (cmd_node->argv)
	//     free_expand(cmd_node->argv);
	
	// if (shell->cmd_path)
	// {
	//     free(shell->cmd_path);
	//     shell->cmd_path = NULL;
	// }
	
	// Outras limpezas específicas conforme necessidade
}

/**
 * exec_free - Compatibilidade com nome usado no projeto de referência
 * Apenas chama cleanup_execution com nome diferente
 */
void	exec_free(t_shell *shell, t_exec *cmd_node)
{
	cleanup_execution(shell, cmd_node);
}
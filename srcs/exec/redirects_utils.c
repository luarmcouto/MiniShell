/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:48:03 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:48:03 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * expand_filename - Expande variáveis no nome do arquivo
 * @shell: estrutura principal
 * @filename: nome do arquivo original
 * 
 * Expande variáveis de ambiente e remove aspas do nome do arquivo
 * Return: nome do arquivo expandido (deve ser liberado)
 */
char	*expand_filename(t_shell *shell, char *filename)
{
	char	*expanded;
	
	if (!filename)
		return (NULL);
		
	// Se já está expandido/processado, apenas duplica
	if (!ft_strchr(filename, '$') && !ft_strchr(filename, '"') 
		&& !ft_strchr(filename, '\''))
		return (ft_strdup(filename));
	
	// Expande variáveis e remove aspas
	expanded = handle_expand(shell, filename, 0);
	if (!expanded)
		expanded = ft_strdup(filename);
		
	return (expanded);
}

/**
 * backup_std_fds - Faz backup dos file descriptors padrão
 * @backup_fds: array para armazenar os backups
 * 
 * Salva stdin, stdout e stderr originais para restaurar depois
 */
void	backup_std_fds(int backup_fds[3])
{
	backup_fds[0] = dup(STDIN_FILENO);   // backup stdin
	backup_fds[1] = dup(STDOUT_FILENO);  // backup stdout  
	backup_fds[2] = dup(STDERR_FILENO);  // backup stderr
}

/**
 * restore_std_fds - Restaura os file descriptors padrão
 * @backup_fds: array com os backups dos fds
 * 
 * Restaura stdin, stdout e stderr originais
 */
void	restore_std_fds(int backup_fds[3])
{
	if (backup_fds[0] >= 0)
	{
		dup2(backup_fds[0], STDIN_FILENO);
		close(backup_fds[0]);
	}
	
	if (backup_fds[1] >= 0)
	{
		dup2(backup_fds[1], STDOUT_FILENO);
		close(backup_fds[1]);
	}
	
	if (backup_fds[2] >= 0)
	{
		dup2(backup_fds[2], STDERR_FILENO);
		close(backup_fds[2]);
	}
}

/**
 * validate_filename - Valida nome do arquivo
 * @shell: estrutura principal
 * @filename: nome do arquivo a validar
 * 
 * Verifica se o nome do arquivo é válido
 * Return: true se válido, false caso contrário
 */
bool	validate_filename(t_shell *shell, char *filename)
{
	if (!filename || !*filename)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		shell->exit_code = 1;
		return (false);
	}
	
	// Verifica se contém espaços (expansão ambígua)
	if (ft_strchr(filename, ' ') || ft_strchr(filename, '\t'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		shell->exit_code = 1;
		return (false);
	}
	
	return (true);
}

/**
 * check_file_permissions - Verifica permissões do arquivo
 * @shell: estrutura principal
 * @filename: nome do arquivo
 * @mode: modo de acesso (R_OK, W_OK, etc.)
 * 
 * Return: true se tiver permissão, false caso contrário
 */
bool	check_file_permissions(t_shell *shell, char *filename, int mode)
{
	if (access(filename, mode) != 0)
	{
		if (mode == R_OK)
			print_file_error(shell, filename, "Permission denied");
		else if (mode == W_OK)
			print_file_error(shell, filename, "Permission denied");
		return (false);
	}
	
	return (true);
}

/**
 * clean_temp_files - Remove arquivos temporários do heredoc
 * @exec_node: nó de execução
 * 
 * Remove todos os arquivos temporários criados para heredocs
 */
void	clean_temp_files(t_exec *exec_node)
{
	t_list	*current;
	t_inf	*infile;

	if (!exec_node || !exec_node->infiles)
		return;
		
	current = exec_node->infiles;
	while (current)
	{
		infile = (t_inf *)current->content;
		
		if (infile->type == HERE && infile->name)
		{
			unlink(infile->name);  // Remove arquivo temporário
		}
		
		current = current->next;
	}
}

/**
 * count_redirections - Conta número de redirecionamentos
 * @exec_node: nó de execução
 * @input_count: ponteiro para contar redirecionamentos de entrada
 * @output_count: ponteiro para contar redirecionamentos de saída
 * 
 * Conta quantos redirecionamentos de cada tipo existem
 */
void	count_redirections(t_exec *exec_node, int *input_count, int *output_count)
{
	t_list	*current;

	*input_count = 0;
	*output_count = 0;
	
	if (!exec_node)
		return;
		
	// Conta redirecionamentos de entrada
	current = exec_node->infiles;
	while (current)
	{
		(*input_count)++;
		current = current->next;
	}
	
	// Conta redirecionamentos de saída
	current = exec_node->outfiles;
	while (current)
	{
		(*output_count)++;
		current = current->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:47:16 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:47:16 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * setup_redirections - Configura redirecionamentos para execução
 * @shell: estrutura principal
 * @exec_node: nó de execução com redirecionamentos
 * 
 * Processa todos os redirecionamentos de entrada e saída
 * na ordem correta para um comando.
 */
void	setup_redirections(t_shell *shell, t_exec *exec_node)
{
	if (!exec_node)
		return;
		
	// Processa redirecionamentos de entrada (< e <<)
	if (exec_node->infiles)
		handle_input_redirections(shell, exec_node->infiles);
	
	// Processa redirecionamentos de saída (> e >>)
	if (exec_node->outfiles)
		handle_output_redirections(shell, exec_node->outfiles);
}

/**
 * handle_input_redirections - Processa redirecionamentos de entrada
 * @shell: estrutura principal
 * @infiles: lista de arquivos de entrada
 * 
 * Processa redirecionamentos < e << (heredoc)
 * O último redirecionamento prevalece
 */
void	handle_input_redirections(t_shell *shell, t_list *infiles)
{
	t_list	*current;
	t_inf	*infile;
	int		fd;
	char	*filename;

	current = infiles;
	while (current)
	{
		infile = (t_inf *)current->content;
		
		if (infile->type == INF)  // < redirecionamento
		{
			filename = expand_filename(shell, infile->eof);
			fd = open_input_file(shell, filename);
			
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			free(filename);
		}
		else if (infile->type == HERE)  // << heredoc
		{
			fd = open_heredoc_file(shell, infile);
			
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		
		current = current->next;
	}
}

/**
 * handle_output_redirections - Processa redirecionamentos de saída
 * @shell: estrutura principal
 * @outfiles: lista de arquivos de saída
 * 
 * Processa redirecionamentos > e >>
 * O último redirecionamento prevalece
 */
void	handle_output_redirections(t_shell *shell, t_list *outfiles)
{
	t_list	*current;
	t_outf	*outfile;
	int		fd;
	char	*filename;

	current = outfiles;
	while (current)
	{
		outfile = (t_outf *)current->content;
		filename = expand_filename(shell, outfile->name);
		
		if (outfile->type == ADD)  // > redirecionamento (truncate)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				print_file_error(shell, filename, "permission denied");
				free(filename);
				return;
			}
		}
		else if (outfile->type == APP)  // >> redirecionamento (append)
		{
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				print_file_error(shell, filename, "permission denied");
				free(filename);
				return;
			}
		}
		
		dup2(fd, STDOUT_FILENO);
		close(fd);
		free(filename);
		
		current = current->next;
	}
}

/**
 * open_input_file - Abre arquivo para leitura
 * @shell: estrutura principal
 * @filename: nome do arquivo expandido
 * 
 * Return: file descriptor ou -1 em caso de erro
 */
int	open_input_file(t_shell *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (access(filename, F_OK) != 0)
			print_file_error(shell, filename, "No such file or directory");
		else
			print_file_error(shell, filename, "Permission denied");
		shell->exit_code = 1;
	}
	
	return (fd);
}

/**
 * open_heredoc_file - Abre arquivo temporário do heredoc
 * @shell: estrutura principal
 * @infile: estrutura do arquivo heredoc
 * 
 * Return: file descriptor ou -1 em caso de erro
 */
int	open_heredoc_file(t_shell *shell, t_inf *infile)
{
	int	fd;

	if (!infile->name)
	{
		ft_putstr_fd("minishell: heredoc file not found\n", 2);
		shell->exit_code = 1;
		return (-1);
	}
	
	fd = open(infile->name, O_RDONLY);
	if (fd < 0)
	{
		print_file_error(shell, infile->name, "heredoc access error");
		shell->exit_code = 1;
	}
	
	return (fd);
}

/**
 * print_file_error - Imprime erros relacionados a arquivos
 * @shell: estrutura principal
 * @filename: nome do arquivo
 * @error_msg: mensagem de erro
 */
void	print_file_error(t_shell *shell, char *filename, char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	shell->exit_code = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:49:06 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:49:06 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * process_heredocs - Processa todos os heredocs de um comando
 * @shell: estrutura principal
 * @exec_node: nó de execução
 * 
 * Percorre todos os heredocs e cria arquivos temporários
 * com o conteúdo lido do usuário
 */
void	process_heredocs(t_shell *shell, t_exec *exec_node)
{
	t_list	*current;
	t_inf	*infile;

	if (!exec_node || !exec_node->infiles)
		return;
		
	current = exec_node->infiles;
	while (current)
	{
		infile = (t_inf *)current->content;
		
		if (infile->type == HERE)
		{
			if (!setup_heredoc(shell, infile))
			{
				shell->exit_code = 1;
				return;
			}
		}
		
		current = current->next;
	}
}

/**
 * setup_heredoc - Configura um heredoc individual
 * @shell: estrutura principal
 * @infile: estrutura do heredoc
 * 
 * Cria arquivo temporário e lê input do usuário até encontrar EOF
 * Return: true se sucesso, false em caso de erro
 */
bool	setup_heredoc(t_shell *shell, t_inf *infile)
{
	int		fd;
	char	*temp_filename;
	bool	should_expand;

	// Determina se deve expandir variáveis (EOF sem aspas)
	should_expand = !has_quotes(infile->eof);
	
	// Remove aspas do EOF se existirem
	infile->eof = remove_quotes(infile->eof);
	
	// Gera nome de arquivo temporário único
	temp_filename = generate_temp_filename(shell, infile->eof);
	if (!temp_filename)
		return (false);
		
	infile->name = temp_filename;
	
	// Cria arquivo temporário
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		print_file_error(shell, temp_filename, "cannot create temp file");
		return (false);
	}
	
	// Lê input do usuário
	if (!read_heredoc_input(shell, infile, fd, should_expand))
	{
		close(fd);
		unlink(temp_filename);
		return (false);
	}
	
	close(fd);
	return (true);
}

/**
 * read_heredoc_input - Lê input do usuário para heredoc
 * @shell: estrutura principal
 * @infile: estrutura do heredoc
 * @fd: file descriptor do arquivo temporário
 * @should_expand: se deve expandir variáveis
 * 
 * Lê linhas do usuário até encontrar o delimitador EOF
 * Return: true se sucesso, false se interrompido
 */
bool	read_heredoc_input(t_shell *shell, t_inf *infile, int fd, bool should_expand)
{
	char	*line;
	char	*expanded_line;
	
	setup_heredoc_signals(shell);
	
	while (1)
	{
		line = readline("> ");
		
		// Ctrl+D ou EOF
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(infile->eof, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		
		// Verifica se é o delimitador EOF
		if (ft_strcmp(line, infile->eof) == 0)
		{
			free(line);
			break;
		}
		
		// Expande variáveis se necessário
		if (should_expand)
			expanded_line = expand_heredoc_line(shell, line);
		else
			expanded_line = ft_strdup(line);
			
		// Escreve linha no arquivo
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		
		free(line);
		free(expanded_line);
		
		// Verifica se foi interrompido por sinal
		if (g_signal_received == SIGINT)
		{
			restore_original_signals();
			return (false);
		}
	}
	
	restore_original_signals();
	return (true);
}

/**
 * generate_temp_filename - Gera nome único para arquivo temporário
 * @shell: estrutura principal
 * @eof_delimiter: delimitador EOF (para tornar nome único)
 * 
 * Gera nome único baseado em PID, timestamp e delimitador
 * Return: nome do arquivo (deve ser liberado)
 */
char	*generate_temp_filename(t_shell *shell, char *eof_delimiter)
{
	char		*filename;
	char		*hash_str;
	static int	counter = 0;
	int			hash;

	// Gera hash simples baseado no delimitador e contador
	hash = (int)getpid() + counter++ + (eof_delimiter ? ft_strlen(eof_delimiter) : 0);
	if (eof_delimiter && *eof_delimiter)
		hash += (int)eof_delimiter[0];
		
	hash_str = ft_itoa(hash);
	if (!hash_str)
		return (NULL);
		
	filename = ft_strjoin("/tmp/.minishell_heredoc_", hash_str);
	free(hash_str);
	
	if (!filename)
		exit_failure(shell, "generate_temp_filename");
		
	return (filename);
}

/**
 * has_quotes - Verifica se string tem aspas
 * @str: string a verificar
 * 
 * Return: true se tem aspas simples ou duplas
 */
bool	has_quotes(char *str)
{
	if (!str)
		return (false);
		
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (true);
		str++;
	}
	
	return (false);
}

/**
 * remove_quotes - Remove aspas de uma string
 * @str: string original
 * 
 * Remove aspas simples ou duplas externas
 * Return: nova string sem aspas (deve ser liberada)
 */
char	*remove_quotes(char *str)
{
	char	*result;
	int		len;
	int		start;
	int		end;

	if (!str || !*str)
		return (ft_strdup(""));
		
	len = ft_strlen(str);
	start = 0;
	end = len - 1;
	
	// Remove aspas externas se existirem
	if ((str[0] == '\'' && str[end] == '\'') || 
	    (str[0] == '"' && str[end] == '"'))
	{
		start = 1;
		end = len - 2;
	}
	
	if (end < start)
		return (ft_strdup(""));
		
	result = ft_substr(str, start, end - start + 1);
	
	// Libera string original se ela tinha aspas
	if (start > 0)
	{
		free(str);
	}
	
	return (result);
}
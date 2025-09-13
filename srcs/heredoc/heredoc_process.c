/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:50:37 by iwietzke          #+#    #+#             */
/*   Updated: 2025/09/12 18:50:37 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Variável global para controle de sinais
volatile sig_atomic_t g_signal_received = 0;

/**
 * setup_heredoc_signals - Configura sinais para heredoc
 * @shell: estrutura principal
 * 
 * Define handlers especiais para Ctrl+C durante heredoc
 */
void	setup_heredoc_signals(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * heredoc_signal_handler - Handler de sinais para heredoc
 * @sig: sinal recebido
 * 
 * Trata Ctrl+C durante leitura de heredoc
 */
void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = SIGINT;
		rl_done = 1;  // Sinaliza para readline terminar
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * restore_original_signals - Restaura sinais originais
 * 
 * Restaura handlers de sinais para estado normal
 */
void	restore_original_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_signal_received = 0;
}

/**
 * process_heredoc_tree - Processa heredocs em árvore binária
 * @shell: estrutura principal
 * @root: raiz da árvore
 * 
 * Percorre a árvore e processa todos os heredocs antes da execução
 */
void	process_heredoc_tree(t_shell *shell, void *root)
{
	if (!root)
		return;
		
	if (((t_node *)root)->type == N_PIPE)
	{
		t_pipe *pipe_node = (t_pipe *)root;
		process_heredoc_tree(shell, pipe_node->left);
		process_heredoc_tree(shell, pipe_node->right);
	}
	else if (((t_node *)root)->type == N_EXEC)
	{
		t_exec *exec_node = (t_exec *)root;
		process_heredocs(shell, exec_node);
	}
}

/**
 * handle_heredoc_interrupt - Trata interrupção de heredoc
 * @shell: estrutura principal
 * @exec_node: nó sendo processado
 * 
 * Limpa arquivos temporários quando heredoc é interrompido
 */
void	handle_heredoc_interrupt(t_shell *shell, t_exec *exec_node)
{
	if (g_signal_received == SIGINT)
	{
		clean_temp_files(exec_node);
		shell->exit_code = 130; // Exit code para SIGINT
		
		ft_putstr_fd("\n", 2);
		restore_original_signals();
	}
}

/**
 * validate_heredoc_syntax - Valida sintaxe dos heredocs
 * @shell: estrutura principal
 * @tokens: lista de tokens
 * 
 * Verifica se todos os heredocs têm delimitadores válidos
 * Return: true se sintaxe válida
 */
bool	validate_heredoc_syntax(t_shell *shell, t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	t_token	*next_token;

	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;
		
		if (token->type == HEREDOC)
		{
			if (!current->next)
			{
				ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
				shell->exit_code = 2;
				return (false);
			}
			
			next_token = (t_token *)current->next->content;
			
			if (next_token->type != WORD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(next_token->value, 2);
				ft_putstr_fd("'\n", 2);
				shell->exit_code = 2;
				return (false);
			}
			
			// Avança para o próximo par
			current = current->next;
		}
		
		current = current->next;
	}
	
	return (true);
}

/**
 * count_heredocs - Conta número de heredocs
 * @exec_node: nó de execução
 * 
 * Return: número de heredocs no comando
 */
int	count_heredocs(t_exec *exec_node)
{
	t_list	*current;
	t_inf	*infile;
	int		count;

	if (!exec_node || !exec_node->infiles)
		return (0);
		
	count = 0;
	current = exec_node->infiles;
	
	while (current)
	{
		infile = (t_inf *)current->content;
		if (infile->type == HERE)
			count++;
		current = current->next;
	}
	
	return (count);
}

/**
 * heredoc_process_fork - Processa heredoc em processo filho
 * @shell: estrutura principal
 * @infile: estrutura do heredoc
 * @fd: file descriptor do arquivo
 * 
 * Cria processo filho para ler heredoc (evita interferência com sinal)
 * Return: true se sucesso
 */
bool	heredoc_process_fork(t_shell *shell, t_inf *infile, int fd)
{
	pid_t	pid;
	int		status;
	bool	should_expand;

	should_expand = !has_quotes(infile->eof);
	
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (false);
	}
	
	if (pid == 0)
	{
		// Processo filho - lê heredoc
		setup_heredoc_signals(shell);
		
		if (read_heredoc_input(shell, infile, fd, should_expand))
			exit(0);
		else
			exit(130); // Interrompido por sinal
	}
	else
	{
		// Processo pai - espera filho
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		
		if (WIFEXITED(status))
		{
			shell->exit_code = WEXITSTATUS(status);
			return (WEXITSTATUS(status) == 0);
		}
		else if (WIFSIGNALED(status))
		{
			shell->exit_code = 128 + WTERMSIG(status);
			return (false);
		}
	}
	
	return (true);
}
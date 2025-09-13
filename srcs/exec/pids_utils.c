/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarmcouto <luarmcouto@student.42porto.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 11:30:00 by luarmcouto        #+#    #+#             */
/*   Updated: 2025/08/09 11:30:00 by luarmcouto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * setup_pipe_fds - Configura file descriptors de pipe
 * @pipefd: array com file descriptors do pipe
 * 
 * Função utilitária para configuração inicial de pipes.
 * Pode ser expandida conforme necessidades específicas do projeto.
 */
void	setup_pipe_fds(int pipefd[])
{
	// Validação básica dos file descriptors
	if (pipefd[0] < 0 || pipefd[1] < 0)
	{
		perror("invalid pipe file descriptors");
		exit(EXIT_FAILURE);
	}
	
	// TODO: Adicionar configurações específicas de pipe se necessário
	// Exemplos: configurar flags, buffer sizes, etc.
}

/**
 * handle_left_process - Gerencia processo filho esquerdo em pipe
 * @shell: estrutura principal do shell
 * @pipefd: file descriptors do pipe
 * @pipe_node: nó de pipe com comandos left/right
 * 
 * Processo filho que executa comando esquerdo do pipe:
 * 1. Fecha extremidade de leitura (pipefd[0])
 * 2. Redireciona stdout para extremidade de escrita (pipefd[1])
 * 3. Fecha pipefd[1] após redirecionamento
 * 4. Executa comando esquerdo recursivamente
 */
void	handle_left_process(t_shell *shell, int pipefd[], t_pipe *pipe_node)
{
	// Fecha extremidade de leitura - não precisa ler do pipe
	close(pipefd[0]);
	
	// Redireciona stdout para pipe - tudo que escrever vai para pipe
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 failed in left process");
		exit(EXIT_FAILURE);
	}
	
	// Fecha file descriptor original após duplicação
	close(pipefd[1]);
	
	// Executa comando esquerdo do pipe
	exec_tree(shell, pipe_node->left);
	
	// Se chegou aqui, algo deu errado na execução
	exit(EXIT_SUCCESS);
}

/**
 * handle_right_process - Gerencia processo filho direito em pipe
 * @shell: estrutura principal do shell
 * @pipefd: file descriptors do pipe
 * @pipe_node: nó de pipe com comandos left/right
 * 
 * Processo filho que executa comando direito do pipe:
 * 1. Fecha extremidade de escrita (pipefd[1])
 * 2. Redireciona stdin para extremidade de leitura (pipefd[0])
 * 3. Fecha pipefd[0] após redirecionamento
 * 4. Executa comando direito recursivamente
 */
void	handle_right_process(t_shell *shell, int pipefd[], t_pipe *pipe_node)
{
	// Fecha extremidade de escrita - não precisa escrever no pipe
	close(pipefd[1]);
	
	// Redireciona stdin para pipe - vai ler do que o comando esquerdo escreveu
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed in right process");
		exit(EXIT_FAILURE);
	}
	
	// Fecha file descriptor original após duplicação
	close(pipefd[0]);
	
	// Executa comando direito do pipe
	exec_tree(shell, pipe_node->right);
	
	// Se chegou aqui, algo deu errado na execução
	exit(EXIT_SUCCESS);
}

/**
 * wait_for_processes - Espera conclusão de processos filhos
 * @pid1: PID do primeiro processo filho
 * @pid2: PID do segundo processo filho
 * @final_status: ponteiro para armazenar status final
 * 
 * Aguarda que ambos os processos filhos terminem e captura
 * o status de saída. O status final será o do último processo
 * (comando direito em pipes), seguindo comportamento do bash.
 */
void	wait_for_processes(pid_t pid1, pid_t pid2, int *final_status)
{
	int	status1;
	int	status2;
	int	wait_result;

	status1 = 0;
	status2 = 0;
	
	// Espera primeiro processo
	wait_result = waitpid(pid1, &status1, 0);
	if (wait_result == -1)
	{
		perror("waitpid failed for first process");
		*final_status = EXIT_FAILURE;
		return ;
	}
	
	// Espera segundo processo
	wait_result = waitpid(pid2, &status2, 0);
	if (wait_result == -1)
	{
		perror("waitpid failed for second process");
		*final_status = EXIT_FAILURE;
		return ;
	}
	
	// Status final é o do segundo processo (comando direito)
	// Extrai código de saída real do status
	if (WIFEXITED(status2))
		*final_status = WEXITSTATUS(status2);
	else if (WIFSIGNALED(status2))
		*final_status = 128 + WTERMSIG(status2);
	else
		*final_status = EXIT_FAILURE;
}

/**
 * handle_pid1 - Compatibilidade com nome usado no projeto de referência
 * Alias para handle_left_process
 */
void	handle_pid1(t_shell *shell, int pipefd[], t_pipe *pipe_node)
{
	handle_left_process(shell, pipefd, pipe_node);
}

/**
 * handle_pid2 - Compatibilidade com nome usado no projeto de referência  
 * Alias para handle_right_process
 */
void	handle_pid2(t_shell *shell, int pipefd[], t_pipe *pipe_node)
{
	handle_right_process(shell, pipefd, pipe_node);
}
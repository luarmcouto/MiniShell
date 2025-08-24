/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarmcouto <luarmcouto@student.42porto.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:30:00 by luarmcouto        #+#    #+#             */
/*   Updated: 2025/08/09 10:30:00 by luarmcouto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * last_exit_status - Gerencia o último código de saída
 * @new_status: novo status a ser armazenado (-1 para consultar)
 * 
 * Função static para armazenar o último código de saída de processo
 * executado, facilitando o controle de fluxo em operadores lógicos
 * 
 * Return: código de saída armazenado
 */
static int	last_exit_status(int new_status)
{
	static int	stored_status = 0;

	if (new_status == -1)
		return (stored_status);
	stored_status = new_status;
	return (stored_status);
}

/**
 * logic_tree_exec - Executa árvore lógica (&&, ||)
 * @shell: estrutura principal do shell
 * @tree_root: raiz da árvore lógica
 * 
 * Implementa a lógica de execução condicional para operadores && e ||:
 * - &&: executa lado direito apenas se esquerdo teve sucesso (exit 0)  
 * - ||: executa lado direito apenas se esquerdo falhou (exit != 0)
 */
void	logic_tree_exec(t_shell *shell, void *tree_root)
{
	(void)shell;
	t_node	*node;

	if (!tree_root)
		return ;
	node = (t_node *)tree_root;
	if (node->type == N_ANDIF)
	{
		logic_tree_exec(shell, ((t_andif *)tree_root)->left);
		last_exit_status(exit_code(-1));
		if (last_exit_status(-1) == 0)
			logic_tree_exec(shell, ((t_andif *)tree_root)->right);
		last_exit_status(exit_code(-1));
	}
	else if (node->type == N_OR)
	{
		logic_tree_exec(shell, ((t_or *)tree_root)->left);
		last_exit_status(exit_code(-1));
		if (last_exit_status(-1) != 0)
			logic_tree_exec(shell, ((t_or *)tree_root)->right);
	}
	else if (node->type == N_PIPE)
		execute_processes(shell, tree_root);
	else if (node->type == N_EXEC)
		execute_processes(shell, tree_root);
}

/**
 * execute_tree - Função principal de execução da árvore
 * @shell: estrutura principal do shell
 * @tree_root: raiz da árvore de comandos
 * 
 * Dispatcher principal que direciona a execução baseada no tipo do nó:
 * - N_PIPE: execução com pipe entre comandos
 * - N_EXEC: execução de comando simples  
 * - N_ANDIF/N_OR: execução lógica condicional
 */
void	execute_tree(t_shell *shell, void *tree_root)
{
	t_node	*node;

	if (!tree_root)
		return ;
	node = (t_node *)tree_root;
	if (node->type == N_PIPE)
		execute_pipe_node(shell, (t_pipe *)tree_root);
	else if (node->type == N_EXEC)
		execute_cmd_node(shell, (t_exec *)tree_root);
	else if (node->type == N_ANDIF || node->type == N_OR)
	{
		logic_tree_exec(shell, tree_root);
		free_env_lst(shell->envp);
		free_shell(shell);
	}
}

/**
 * start_execution - Função de entrada para execução
 * @shell: estrutura principal do shell
 * @tree_root: raiz da árvore de comandos construída
 * 
 * Função principal chamada do terminal para iniciar a execução.
 * Esta é a interface entre o sistema de parsing e o sistema de execução.
 */
void	start_execution(t_shell *shell, void *tree_root)
{
	if (!tree_root || !shell)
		return ;
	
	// Executa a árvore de comandos
	execute_tree(shell, tree_root);
}

/**
 * execute_pipe_node - Executa nó de pipe
 * @shell: estrutura principal do shell  
 * @pipe_node: nó de pipe com comandos left/right
 * 
 * Cria pipe, faz fork para cada lado do pipe e coordena a comunicação:
 * - Processo filho esquerdo: escreve no pipe (stdout -> pipe[1])
 * - Processo filho direito: lê do pipe (pipe[0] -> stdin)
 * - Processo pai: espera ambos os filhos terminarem
 */
void	execute_pipe_node(t_shell *shell, t_pipe *pipe_node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		final_status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe creation failed");
		exit(EXIT_FAILURE);
	}
	final_status = 0;
	left_pid = fork();
	if (left_pid == 0)
		handle_left_process(shell, pipefd, pipe_node);
	right_pid = fork();
	if (right_pid == 0)
		handle_right_process(shell, pipefd, pipe_node);
	
	// Processo pai fecha pipes e espera filhos
	close(pipefd[0]);
	close(pipefd[1]);
	wait_for_processes(left_pid, right_pid, &final_status);
	//exit_status(final_status);
	free_env_lst(shell->envp);
	free_shell(shell);
	exit(exit_code(-1));
}

/**
 * execute_cmd_node - Executa nó de comando simples
 * @shell: estrutura principal do shell
 * @cmd_node: nó de execução com comando e argumentos
 * 
 * Executa comando simples (não-pipe):
 * 1. Processa redirecionamentos (arquivos de entrada/saída)
 * 2. Expande variáveis nos argumentos  
 * 3. Verifica se é builtin e executa apropriadamente
 * 4. Resolve caminho do comando se não for builtin
 * 5. Executa comando via execve()
 */
void	execute_cmd_node(t_shell *shell, t_exec *cmd_node)
{
	int	ret_code;

	// TODO: Implementar check_files_order() para redirecionamentos
	// check_files_order(shell, cmd_node);
	
	// TODO: Implementar expand_argv() para expansão de variáveis
	// cmd_node->argv = expand_argv(shell, cmd_node->argv);
	
	// TODO: Implementar check para wildcards se necessário
	// check_wildcards(shell, cmd_node);
	
	// Verifica se é builtin
	if (cmd_node->command && is_builtin(cmd_node->command))
	{
		ret_code = exec_builtin(shell, cmd_node);
		cleanup_execution(shell, cmd_node);
		exit(ret_code);
	}
	
	// TODO: Configurar sinais para processo filho
	// set_fork1_signal();
	
	// Resolve caminho do comando
	shell->cmd_path = resolve_command_path(shell, shell->path, 
		cmd_node->argv[0]);
	
	// TODO: Verificar se é diretório
	// if (cmd_node->argv)
	//     is_directory(shell, cmd_node->argv);
	
	// Executa comando
	if (execve(shell->cmd_path, cmd_node->argv, shell->envp_arr) < 0)
	{
		free_env_lst(shell->envp);
		if (cmd_node->argv && cmd_node->argv[0])
		{
			// TODO: Implementar free_expand()
			// free_expand(cmd_node->argv);
			// TODO: Implementar exec_failure() para tratamento de erro  
			// exec_failure(shell, shell->cmd_path);
		}
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
}

/**
 * Funções de compatibilidade com nomes do projeto de referência
 * Estas funções mantêm a interface original enquanto usam nossa implementação
 */

/**
 * exec_tree - Compatibilidade com nome original
 * Chama execute_tree com nossa implementação
 */
void	exec_tree(t_shell *shell, void *root)
{
	execute_tree(shell, root);
}

/**
 * exec_pipe - Compatibilidade com nome original
 * Chama execute_pipe_node com nossa implementação
 */
void	exec_pipe(t_shell *shell, t_pipe *pipe_node)
{
	execute_pipe_node(shell, pipe_node);
}

/**
 * exec_node - Compatibilidade com nome original
 * Chama execute_cmd_node com nossa implementação
 */
void	exec_node(t_shell *shell, t_exec *exec_node)
{
	execute_cmd_node(shell, exec_node);
}

/**
 * lexec_tree - Compatibilidade com nome original
 * Chama logic_tree_exec com nossa implementação
 */
void	lexec_tree(t_shell *shell, void *root)
{
	logic_tree_exec(shell, root);
}
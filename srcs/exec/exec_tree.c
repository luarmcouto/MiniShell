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

void	lexec_tree(t_shell *shell, void *root)
{
	t_node	*node;

	if (!root)
		return ;
	node = (t_node *)root;
	if (node->type == N_ANDIF)
	{
		lexec_tree(shell, ((t_andif *)root)->left);
		last_process(exit_code(-1));
		if (last_process(-1) == 0)
			lexec_tree(shell, ((t_andif *)root)->right);
		last_process(exit_code(-1));
	}
	else if (node->type == N_OR)
	{
		lexec_tree(shell, ((t_or *)root)->left);
		last_process(exit_code(-1));
		if (last_process(-1) != 0)
			lexec_tree(shell, ((t_or *)root)->right);
	}
	else if (node->type == N_PIPE)
		exec_tree(shell, root);
	else if (node->type == N_EXEC)
		exec_tree(shell, root);
	return ;
}

void	exec_tree(t_shell *shell, void *root)
{
	if (!root)
		return;
		
	if (((t_node *)root)->type == N_PIPE)
		exec_pipe(shell, root);
	else if (((t_node *)root)->type == N_EXEC)
		exec_node(shell, root);
	else if (((t_node *)root)->type == N_ANDIF)
	{
		lexec_tree(shell, root);
		free_env_list(shell->envp);
		free_shell(shell);
	}
	else if (((t_node *)root)->type == N_OR)
	{
		lexec_tree(shell, root);
		free_env_list(shell->envp);
		free_shell(shell);
	}
}

void	exec_pipe(t_shell *shell, t_pipe *pipe_node)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	status = 0;
	pid1 = fork();
	if (pid1 == 0)
		handle_pid1(shell, pipefd, pipe_node);
	pid2 = fork();
	if (pid2 == 0)
		handle_pid2(shell, pipefd, pipe_node);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
	free_env_list(shell->envp);
	free_shell(shell);
	exit(exit_code(-1));
}

void	exec_node(t_shell *shell, t_exec *exec_node)
{
	int		ret;

	if (!exec_node)
		return;
		
	// Processa redirecionamentos primeiro (USANDO NOSSA IMPLEMENTAÇÃO)
	setup_redirections(shell, exec_node);
	
	// Expande argumentos
	exec_node->argv = expand_argv(shell, exec_node->argv);
	
	// Verifica wildcards se implementado
	// check_wildcards(shell, exec_node);
	
	// Executa built-in se for o caso
	if (exec_node->command && is_builtin_command(exec_node->command))
	{
		ret = execute_shell_builtin(shell, exec_node);
		shell->exit_code = ret;  // Define exit code sem sair
		return;  // Retorna para continuar o shell
	}
	
	// Para comandos externos, cria processo filho
	pid_t pid = fork();
	if (pid == 0)
	{
		// Processo filho - executa comando externo
		
		// Configura sinais para processo filho
		// set_fork1_signal();
		
		// Encontra caminho do comando
		shell->cmd_path = find_cmd_path(shell, shell->path, exec_node->argv[0]);
		
		// Verifica se é diretório
		// is_directory(shell, exec_node->argv);
		
		// Executa comando externo
		if (execve(shell->cmd_path, exec_node->argv, shell->envp_arr) < 0)
		{
			free_env_list(shell->envp);
			if (exec_node->argv && exec_node->argv[0])
			{
				free_expand(exec_node->argv);
				exit_failure(shell, shell->cmd_path);
			}
			free_shell(shell);
			exit(0);
		}
	}
	else if (pid > 0)
	{
		// Processo pai - espera o filho
		int status;
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
	else
	{
		// Erro no fork
		perror("fork failed");
		shell->exit_code = 1;
	}
	
	free_expand(exec_node->argv);
}
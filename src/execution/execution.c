#include "minishell.h"

static int	execute_single_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_FAILURE);

	// Se for built-in, executa diretamente
	if (is_builtin(cmd->args[0]))
	{
		// Aplica redirecionamentos para built-ins também
		if (apply_redirections(cmd) == -1)
			return (EXIT_FAILURE);
		
		result = execute_builtin(cmd);
		g_last_exit_status = result;
		return (result);
	}

	// Fork para executar comando externo
	pid = fork();
	if (pid == -1)
		return (handle_fork_error());
	else if (pid == 0)
	{
		// Processo filho
		
		// Aplica redirecionamentos
		if (apply_redirections(cmd) == -1)
			exit(EXIT_FAILURE);
		
		// Se não temos path, tenta encontrar
		if (!cmd->path)
			cmd->path = find_cmd_path(cmd->args[0], envp);
		
		if (!cmd->path)
		{
			handle_exec_error(cmd->args[0], ENOENT);
			exit(EXIT_NOT_FOUND);
		}
		
		// Verifica se o comando é válido e executável
		result = check_command_access(cmd->path);
		if (result != EXIT_SUCCESS)
			exit(result);
		
		// Executa o comando
		execve(cmd->path, cmd->args, envp);
		
		// Se chegou aqui, execve falhou
		handle_exec_error(cmd->path, errno);
		exit(EXIT_EXEC_FAIL);
	}
	else
	{
		// Processo pai - espera o filho
		waitpid(pid, &status, 0);
		update_exit_status(status);
		return (g_last_exit_status);
	}
}

static int	execute_pipeline(t_cmd *cmds, char **envp)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	int		status;
	int		last_status;

	current = cmds;
	prev_fd = -1;
	last_status = 0;

	while (current)
	{
		// Se há próximo comando, cria pipe
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
				return (handle_pipe_error());
		}

		pid = fork();
		if (pid == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			return (handle_fork_error());
		}
		else if (pid == 0)
		{
			// Processo filho
			
			// Conecta entrada do pipe anterior
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
				{
					perror("dup2 prev_fd");
					exit(EXIT_FAILURE);
				}
				close(prev_fd);
			}
			
			// Conecta saída para próximo pipe
			if (current->next)
			{
				close(pipe_fd[0]); // Fecha leitura
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2 pipe_fd");
					exit(EXIT_FAILURE);
				}
				close(pipe_fd[1]);
			}
			
			// Aplica redirecionamentos específicos do comando
			if (apply_redirections(current) == -1)
				exit(EXIT_FAILURE);
			
			// Executa built-in ou comando externo
			if (is_builtin(current->args[0]))
				exit(execute_builtin(current));
			else
			{
				if (!current->path)
					current->path = find_cmd_path(current->args[0], envp);
				
				if (!current->path)
				{
					handle_exec_error(current->args[0], ENOENT);
					exit(EXIT_NOT_FOUND);
				}
				
				if (check_command_access(current->path) != EXIT_SUCCESS)
					exit(g_last_exit_status);
				
				execve(current->path, current->args, envp);
				handle_exec_error(current->path, errno);
				exit(EXIT_EXEC_FAIL);
			}
		}
		else
		{
			// Processo pai
			
			// Fecha pipe anterior se existir
			if (prev_fd != -1)
				close(prev_fd);
			
			// Se criou pipe, fecha escrita e salva leitura
			if (current->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			
			// Se é o último comando, espera
			if (!current->next)
			{
				waitpid(pid, &status, 0);
				update_exit_status(status);
				last_status = g_last_exit_status;
			}
		}
		
		current = current->next;
	}
	
	// Espera todos os processos filhos restantes
	while (wait(NULL) > 0)
		;
	
	return (last_status);
}

void	execute_commands(t_cmd *cmds, char **envp)
{
	int	exit_status;

	if (!cmds)
		return;

	// Se há apenas um comando (sem pipe)
	if (!cmds->next)
		exit_status = execute_single_cmd(cmds, envp);
	else
		exit_status = execute_pipeline(cmds, envp);

	// O exit status já foi salvo globalmente pelas funções acima
	(void)exit_status;
}
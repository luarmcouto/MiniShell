#include "minishell.h"

static int	execute_single_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	// Se for built-in, executa diretamente
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd));

	// Fork para executar comando externo
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		// Processo filho
		// TODO: Aplicar redirecionamentos aqui
		
		// Se não temos path, tenta encontrar
		if (!cmd->path)
			cmd->path = find_cmd_path(cmd->args[0], envp);
		
		if (!cmd->path)
		{
			printf("minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		
		// Executa o comando
		if (execve(cmd->path, cmd->args, envp) == -1)
		{
			perror("execve");
			exit(126);
		}
	}
	else
	{
		// Processo pai - espera o filho
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
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
		if (current->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return (1);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			// Processo filho
			
			// Conecta entrada do pipe anterior
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			
			// Conecta saída para próximo pipe
			if (current->next)
			{
				close(pipe_fd[0]); // Fecha leitura
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			
			// TODO: Aplicar redirecionamentos específicos do comando
			
			// Executa built-in ou comando externo
			if (is_builtin(current->args[0]))
				exit(execute_builtin(current));
			else
			{
				if (!current->path)
					current->path = find_cmd_path(current->args[0], envp);
				
				if (!current->path)
				{
					printf("minishell: %s: command not found\n", current->args[0]);
					exit(127);
				}
				
				execve(current->path, current->args, envp);
				perror("execve");
				exit(126);
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
				last_status = WEXITSTATUS(status);
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

	// TODO: Salvar exit_status em uma variável global ou estrutura
	// para expansão de $? no parser
	(void)exit_status;
}
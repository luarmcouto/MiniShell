#include "minishell.h"

// Códigos de erro padrão do shell
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1
#define EXIT_MISUSE         2
#define EXIT_EXEC_FAIL      126
#define EXIT_NOT_FOUND      127
#define EXIT_INVALID_EXIT   128
#define EXIT_SIGNAL_BASE    128

// Variável global para guardar último exit status
int g_last_exit_status = 0;

// Função para imprimir erro formatado
void	print_error(char *cmd, char *arg, char *message)
{
	fprintf(stderr, "minishell: ");
	if (cmd)
		fprintf(stderr, "%s: ", cmd);
	if (arg)
		fprintf(stderr, "%s: ", arg);
	if (message)
		fprintf(stderr, "%s", message);
	fprintf(stderr, "\n");
}

// Função para tratar erros de execução
int	handle_exec_error(char *cmd, int error_code)
{
	switch (error_code)
	{
		case ENOENT:
			// Comando não encontrado
			print_error(cmd, NULL, "command not found");
			g_last_exit_status = EXIT_NOT_FOUND;
			return (EXIT_NOT_FOUND);
			
		case EACCES:
			// Permissão negada
			print_error(cmd, NULL, "Permission denied");
			g_last_exit_status = EXIT_EXEC_FAIL;
			return (EXIT_EXEC_FAIL);
			
		case ENOEXEC:
			// Arquivo não é executável
			print_error(cmd, NULL, "cannot execute binary file");
			g_last_exit_status = EXIT_EXEC_FAIL;
			return (EXIT_EXEC_FAIL);
			
		case ENOMEM:
			// Sem memória
			print_error(cmd, NULL, "cannot allocate memory");
			g_last_exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
			
		default:
			// Erro genérico
			print_error(cmd, NULL, strerror(error_code));
			g_last_exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
	}
}

// Função para tratar erros de redirecionamento
int	handle_redirect_error(char *filename, int error_code)
{
	switch (error_code)
	{
		case ENOENT:
			print_error(NULL, filename, "No such file or directory");
			break;
			
		case EACCES:
			print_error(NULL, filename, "Permission denied");
			break;
			
		case EISDIR:
			print_error(NULL, filename, "Is a directory");
			break;
			
		case EMFILE:
		case ENFILE:
			print_error(NULL, filename, "Too many open files");
			break;
			
		default:
			print_error(NULL, filename, strerror(error_code));
			break;
	}
	
	g_last_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

// Função para tratar erros de fork
int	handle_fork_error(void)
{
	print_error(NULL, NULL, "fork failed");
	g_last_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

// Função para tratar erros de pipe
int	handle_pipe_error(void)
{
	print_error(NULL, NULL, "pipe failed");
	g_last_exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

// Função para verificar se um path é válido e executável
int	check_command_access(char *path)
{
	struct stat	statbuf;

	if (!path)
		return (0);

	// Verifica se o arquivo existe
	if (stat(path, &statbuf) == -1)
		return (handle_exec_error(path, errno));

	// Verifica se é um diretório
	if (S_ISDIR(statbuf.st_mode))
	{
		print_error(path, NULL, "Is a directory");
		g_last_exit_status = EXIT_EXEC_FAIL;
		return (EXIT_EXEC_FAIL);
	}

	// Verifica se é executável
	if (access(path, X_OK) == -1)
		return (handle_exec_error(path, errno));

	return (EXIT_SUCCESS);
}

// Função para atualizar exit status após execução
void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_status = EXIT_SIGNAL_BASE + WTERMSIG(status);
	else
		g_last_exit_status = EXIT_FAILURE;
}

// Função para obter o último exit status (para expansão de $?)
int	get_last_exit_status(void)
{
	return (g_last_exit_status);
}

// Função para cleanup em caso de erro crítico
void	cleanup_and_exit(t_cmd *cmds, int exit_code)
{
	if (cmds)
		free_cmds(cmds);
	
	// TODO: Cleanup de outras estruturas quando implementadas
	// como environment, history, etc.
	
	exit(exit_code);
}
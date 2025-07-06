#include "minishell.h"

// Lista dos comandos built-in
static char	*g_builtins[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit",
	NULL
};

int	is_builtin(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);

	i = 0;
	while (g_builtins[i])
	{
		if (ft_strcmp(cmd, g_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		newline;

	newline = 1;
	i = 1;

	// Verifica se tem a opção -n
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	// Imprime os argumentos
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");

	return (0);
}

static int	builtin_pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd; // pwd não usa argumentos no nosso caso
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static int	builtin_env(t_cmd *cmd)
{
	extern char	**environ;
	int			i;

	(void)cmd; // env não usa argumentos no nosso caso
	
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

static int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	char	*home;

	// Se não tem argumentos, vai para HOME
	if (!cmd->args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
		path = cmd->args[1];

	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	
	return (0);
}

static int	builtin_export(t_cmd *cmd)
{
	// TODO: Implementar export completo
	// Por enquanto, versão simples que só mostra o que seria exportado
	int	i;

	if (!cmd->args[1])
	{
		// Se não tem argumentos, mostra todas as variáveis
		// TODO: Implementar listagem de variáveis exportadas
		printf("export: usage: export [name[=value]]\n");
		return (0);
	}

	i = 1;
	while (cmd->args[i])
	{
		// TODO: Validar formato da variável
		// TODO: Adicionar à lista de variáveis exportadas
		printf("export: %s (not implemented yet)\n", cmd->args[i]);
		i++;
	}
	
	return (0);
}

static int	builtin_unset(t_cmd *cmd)
{
	// TODO: Implementar unset completo
	int	i;

	if (!cmd->args[1])
	{
		printf("unset: usage: unset [name ...]\n");
		return (0);
	}

	i = 1;
	while (cmd->args[i])
	{
		// TODO: Remover variável do ambiente
		printf("unset: %s (not implemented yet)\n", cmd->args[i]);
		i++;
	}
	
	return (0);
}

static int	builtin_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	
	// Se tem argumento, usa como código de saída
	if (cmd->args[1])
	{
		exit_code = ft_atoi(cmd->args[1]);
		// TODO: Validar se o argumento é um número válido
	}

	printf("exit\n");
	exit(exit_code);
}

int	execute_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);

	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(cmd));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd));

	return (1);
}
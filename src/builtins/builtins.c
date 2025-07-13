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

// ECHO melhorado - suporte completo a -n
static int	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		newline;
	int		arg_start;

	newline = 1;
	arg_start = 1;

	// Processa todas as flags -n consecutivas
	while (cmd->args[arg_start] && ft_strcmp(cmd->args[arg_start], "-n") == 0)
	{
		newline = 0;
		arg_start++;
	}

	// Imprime os argumentos restantes
	i = arg_start;
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

// PWD melhorado - com tratamento de erro
static int	builtin_pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd; // pwd não precisa de argumentos

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		// Se getcwd falhar, tenta usar PWD do ambiente
		cwd = getenv("PWD");
		if (cwd)
		{
			printf("%s\n", cwd);
			return (0);
		}
		perror("pwd");
		return (1);
	}

	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

// ENV melhorado - com suporte a argumentos simples
static int	builtin_env(t_cmd *cmd)
{
	extern char	**environ;
	int			i;

	// Se tem argumentos, env básico do minishell não suporta
	if (cmd->args[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (127);
	}

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

// CD melhorado - com suporte a "-" e melhor error handling
static int	builtin_cd(t_cmd *cmd)
{
	char	*path;
	char	*home;
	char	*oldpwd;
	char	*current_pwd;

	// Salva diretório atual antes de mudar
	current_pwd = getcwd(NULL, 0);

	// Determina o destino
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
	{
		// cd sem argumentos ou cd ~ - vai para HOME
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			if (current_pwd)
				free(current_pwd);
			return (1);
		}
		path = home;
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		// cd - vai para diretório anterior
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			if (current_pwd)
				free(current_pwd);
			return (1);
		}
		path = oldpwd;
		printf("%s\n", path); // cd - imprime o destino
	}
	else
	{
		path = cmd->args[1];
	}

	// Tenta mudar de diretório
	if (chdir(path) == -1)
	{
		perror("cd");
		if (current_pwd)
			free(current_pwd);
		return (1);
	}

	// TODO: Atualizar variáveis PWD e OLDPWD no ambiente
	// Por enquanto só funciona, na semana 3 implementaremos environment completo
	
	if (current_pwd)
		free(current_pwd);
	return (0);
}

// EXIT melhorado - com validação de argumentos
static int	builtin_exit(t_cmd *cmd)
{
	int		exit_code;
	long	result;
	char	*endptr;

	exit_code = 0;

	printf("exit\n");

	// Se tem argumentos
	if (cmd->args[1])
	{
		// Verifica se é um número válido
		result = strtol(cmd->args[1], &endptr, 10);
		
		if (*endptr != '\0' || cmd->args[1] == endptr)
		{
			// Argumento não é numérico
			printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
			exit(2);
		}
		
		// Verifica se tem muitos argumentos
		if (cmd->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return (1); // Não sai, só retorna erro
		}
		
		exit_code = (int)result;
	}

	exit(exit_code);
}

// EXPORT e UNSET básicos - implementação completa na semana 3
static int	builtin_export(t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		// TODO: Mostrar todas as variáveis exportadas
		printf("export: basic implementation - showing all env vars:\n");
		return (builtin_env(cmd));
	}

	i = 1;
	while (cmd->args[i])
	{
		// TODO: Implementar export real na semana 3
		printf("export: would export '%s' (not implemented yet)\n", cmd->args[i]);
		i++;
	}

	return (0);
}

static int	builtin_unset(t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
		return (0); // unset sem argumentos não faz nada

	i = 1;
	while (cmd->args[i])
	{
		// TODO: Implementar unset real na semana 3
		printf("unset: would unset '%s' (not implemented yet)\n", cmd->args[i]);
		i++;
	}

	return (0);
}

// Função principal para executar built-ins
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
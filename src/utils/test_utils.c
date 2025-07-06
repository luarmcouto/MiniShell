#include "minishell.h"

// Função temporária para criar comando de teste
// Remove quando o parser estiver pronto
t_cmd	*create_test_cmd(char *input)
{
	t_cmd	*cmd;
	char	**tokens;
	int		i;

	if (!input || !*input)
		return (NULL);

	// Aloca o comando
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	// Inicializa estrutura
	cmd->path = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->next = NULL;

	// Parse simples por espaços (temporário)
	tokens = ft_split(input, ' ');
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}

	// Conta argumentos
	i = 0;
	while (tokens[i])
		i++;

	// Aloca array de argumentos (+1 para NULL)
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
	{
		// Libera tokens
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		free(cmd);
		return (NULL);
	}

	// Copia argumentos
	i = 0;
	while (tokens[i])
	{
		cmd->args[i] = ft_strdup(tokens[i]);
		if (!cmd->args[i])
		{
			// Libera o que já foi alocado
			while (--i >= 0)
				free(cmd->args[i]);
			free(cmd->args);
			
			// Libera tokens
			i = 0;
			while (tokens[i])
				free(tokens[i++]);
			free(tokens);
			free(cmd);
			return (NULL);
		}
		i++;
	}
	cmd->args[i] = NULL;

	// Libera tokens
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);

	return (cmd);
}
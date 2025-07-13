/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:17:09 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/07/07 13:55:09 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função para contar argumentos em uma lista de tokens
static int count_word_tokens(t_token *tokens)
{
	int count = 0;
	t_token *current = tokens;
	
	while (current && current->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// Função para criar array de argumentos a partir dos tokens
static char **create_args_array(t_token **tokens)
{
	int arg_count = count_word_tokens(*tokens);
	char **args;
	int i = 0;
	t_token *current = *tokens;
	
	if (arg_count == 0)
		return (NULL);
	
	// Aloca array (+1 para NULL terminator)
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	
	// Copia os argumentos
	while (current && current->type == TOKEN_WORD && i < arg_count)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
		{
			// Libera o que já foi alocado
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	args[i] = NULL;
	
	// Avança o ponteiro de tokens
	*tokens = current;
	return (args);
}

/*// Função para processar redirecionamentos (versão simples)
static int process_redirections(t_token **tokens, t_cmd *cmd)
{
	t_token *current = *tokens;
	(void)cmd;
	
	while (current && (current->type == TOKEN_REDIRECT_IN || 
					   current->type == TOKEN_REDIRECT_OUT || 
					   current->type == TOKEN_APPEND))
	{
		if (current->type == TOKEN_REDIRECT_IN)
		{
			// < arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// TODO: Na semana 2, implementar abertura real do arquivo
			// Por enquanto, só guarda o nome
			printf("DEBUG: Input redirection to '%s'\n", current->value);
			current = current->next;
		}
		else if (current->type == TOKEN_REDIRECT_OUT)
		{
			// > arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// TODO: Na semana 2, implementar abertura real do arquivo
			printf("DEBUG: Output redirection to '%s'\n", current->value);
			current = current->next;
		}
		else if (current->type == TOKEN_APPEND)
		{
			// >> arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// TODO: Na semana 2, implementar abertura real do arquivo
			printf("DEBUG: Append redirection to '%s'\n", current->value);
			current = current->next;
		}
	}
	
	*tokens = current;
	return (1);
}*/
// Substitua a função process_redirections no parser.c por esta versão:

static int process_redirections(t_token **tokens, t_cmd *cmd)
{
	t_token *current = *tokens;
	
	while (current && (current->type == TOKEN_REDIRECT_IN || 
					   current->type == TOKEN_REDIRECT_OUT || 
					   current->type == TOKEN_APPEND))
	{
		if (current->type == TOKEN_REDIRECT_IN)
		{
			// < arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// AGORA REALMENTE PROCESSA O REDIRECIONAMENTO
			if (process_redirection_token(cmd, current->value, TOKEN_REDIRECT_IN) == -1)
				return (0);
			
			current = current->next;
		}
		else if (current->type == TOKEN_REDIRECT_OUT)
		{
			// > arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// AGORA REALMENTE PROCESSA O REDIRECIONAMENTO
			if (process_redirection_token(cmd, current->value, TOKEN_REDIRECT_OUT) == -1)
				return (0);
				
			current = current->next;
		}
		else if (current->type == TOKEN_APPEND)
		{
			// >> arquivo
			current = current->next;
			if (!current || current->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			
			// AGORA REALMENTE PROCESSA O REDIRECIONAMENTO
			if (process_redirection_token(cmd, current->value, TOKEN_APPEND) == -1)
				return (0);
				
			current = current->next;
		}
	}
	
	*tokens = current;
	return (1);
}

// Função para parsear um comando simples (sem pipes)
static t_cmd *parse_simple_command(t_token **tokens)
{
	t_cmd *cmd;
	
	if (!tokens || !*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	
	// Aloca comando
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	
	// Inicializa estrutura
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->next = NULL;
	
	// Extrai argumentos (comando + argumentos)
	cmd->args = create_args_array(tokens);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	
	// Processa redirecionamentos (se houver)
	if (!process_redirections(tokens, cmd))
	{
		// Erro de sintaxe nos redirecionamentos
		free_cmds(cmd);
		return (NULL);
	}
	
	return (cmd);
}

// Função principal de parsing (versão simples, sem pipes ainda)
t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd *cmd;
	
	if (!tokens)
		return (NULL);
	
	// Por enquanto, só parseia comandos simples
	// Na semana 3, implementaremos pipes
	cmd = parse_simple_command(&tokens);
	
	// Verifica se sobrou algum token não processado
	if (tokens && tokens->type == TOKEN_PIPE)
	{
		printf("minishell: pipes will be implemented in week 3\n");
		free_cmds(cmd);
		return (NULL);
	}
	
	return (cmd);
}

// Função integrada que combina tokenização e parsing
t_cmd *parse_input(char *input)
{
	t_token *tokens;
	t_cmd *cmd;
	
	if (!input || !*input)
		return (NULL);
	
	// Tokeniza a entrada
	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	
	// DEBUG: Comentado para não poluir a saída
	// print_tokens(tokens);
	
	// Parseia os tokens
	cmd = parse_tokens(tokens);
	
	// Libera tokens
	free_tokens(tokens);
	
	return (cmd);
}

// Função para validação sintática básica
int validate_syntax(t_token *tokens)
{
	t_token *current = tokens;
	
	if (!tokens)
		return (0);
	
	// Não pode começar com operador
	if (current->type != TOKEN_WORD)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", current->value);
		return (0);
	}
	
	while (current)
	{
		// Redirecionamentos devem ser seguidos por palavras
		if ((current->type == TOKEN_REDIRECT_IN || 
			 current->type == TOKEN_REDIRECT_OUT || 
			 current->type == TOKEN_APPEND || 
			 current->type == TOKEN_HEREDOC) && 
			(!current->next || current->next->type != TOKEN_WORD))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		
		// Pipes devem ser seguidos por palavras
		if (current->type == TOKEN_PIPE && 
			(!current->next || current->next->type != TOKEN_WORD))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", 
				   current->next ? current->next->value : "newline");
			return (0);
		}
		
		current = current->next;
	}
	
	return (1);
}
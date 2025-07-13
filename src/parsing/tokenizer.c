/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:17:07 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/07/07 13:54:06 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função para pular espaços em branco
static char *skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	return (str);
}

// Função para identificar operadores
static t_token_type get_operator_type(char *str, int *len)
{
	if (str[0] == '|')
	{
		*len = 1;
		return (TOKEN_PIPE);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			*len = 2;
			return (TOKEN_HEREDOC);
		}
		*len = 1;
		return (TOKEN_REDIRECT_IN);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
		{
			*len = 2;
			return (TOKEN_APPEND);
		}
		*len = 1;
		return (TOKEN_REDIRECT_OUT);
	}
	return (TOKEN_WORD);
}

// Função para extrair uma palavra com aspas (até encontrar espaço ou operador)
static char *extract_word(char *str, int *len)
{
	char *start = str;
	char quote_char = 0;
	int word_len = 0;
	char *word;
	int i = 0;
	
	*len = 0;

	// Verifica se começa com aspas
	if (*str == '"' || *str == '\'')
	{
		quote_char = *str;
		str++;
		(*len)++;
		start = str; // start aponta para depois da aspa
	}

	// Se tem aspas, vai até encontrar a aspa de fechamento
	if (quote_char)
	{
		while (*str && *str != quote_char)
		{
			str++;
			(*len)++;
			word_len++;
		}
		if (*str == quote_char)
		{
			(*len)++; // conta a aspa de fechamento para avançar o ponteiro
			// mas word_len não inclui as aspas
		}
	}
	else
	{
		// Sem aspas, vai até espaço ou operador
		while (*str && *str != ' ' && *str != '\t' && *str != '\n' &&
			   *str != '|' && *str != '<' && *str != '>')
		{
			str++;
			(*len)++;
			word_len++;
		}
	}
	
	if (word_len == 0)
		return (NULL);
	
	// Aloca e copia só o conteúdo (sem aspas)
	word = malloc(word_len + 1);
	if (!word)
		return (NULL);
	
	while (i < word_len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	
	return (word);
}

// Função para criar um novo token
static t_token *create_token(char *value, t_token_type type)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

// Função para adicionar token ao final da lista
static void add_token(t_token **tokens, t_token *new_token)
{
	t_token *current;
	
	if (!*tokens)
	{
		*tokens = new_token;
		return;
	}
	
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

// Função para verificar se as aspas estão balanceadas
static int check_quotes(char *input)
{
	int single_quotes = 0;
	int double_quotes = 0;
	
	while (*input)
	{
		if (*input == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		else if (*input == '"' && single_quotes % 2 == 0)
			double_quotes++;
		input++;
	}
	
	if (single_quotes % 2 != 0)
	{
		printf("minishell: syntax error: unclosed single quote\n");
		return (0);
	}
	if (double_quotes % 2 != 0)
	{
		printf("minishell: syntax error: unclosed double quote\n");
		return (0);
	}
	return (1);
}

// Função principal de tokenização
t_token *tokenize(char *input)
{
	t_token *tokens = NULL;
	char *current = input;
	int len;
	
	if (!input || !*input)
		return (NULL);
	
	// Verifica aspas balanceadas antes de tokenizar
	if (!check_quotes(input))
		return (NULL);
	
	while (*current)
	{
		// Pula espaços
		current = skip_whitespace(current);
		if (!*current)
			break;
		
		// Verifica se é operador
		t_token_type op_type = get_operator_type(current, &len);
		if (op_type != TOKEN_WORD)
		{
			// É um operador
			char *op_value = malloc(len + 1);
			if (!op_value)
			{
				free_tokens(tokens);
				return (NULL);
			}
			ft_strlcpy(op_value, current, len + 1);
			
			t_token *token = create_token(op_value, op_type);
			if (!token)
			{
				free(op_value);
				free_tokens(tokens);
				return (NULL);
			}
			
			add_token(&tokens, token);
			current += len;
		}
		else
		{
			// É uma palavra
			char *word = extract_word(current, &len);
			if (!word)
				break;
			
			t_token *token = create_token(word, TOKEN_WORD);
			if (!token)
			{
				free(word);
				free_tokens(tokens);
				return (NULL);
			}
			
			add_token(&tokens, token);
			current += len;
		}
	}
	
	return (tokens);
}

// Função para liberar tokens
void free_tokens(t_token *tokens)
{
	t_token *current = tokens;
	t_token *next;
	
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

// Função para debug - imprimir tokens
void print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	char *type_names[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "APPEND", "HEREDOC", "EOF"};
	
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("Type: %-12s Value: '%s'\n", type_names[current->type], current->value);
		current = current->next;
	}
	printf("===============\n");
}
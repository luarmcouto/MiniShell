/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:21:22 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:18:29 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * get_argv - Constrói array de argumentos para o comando
 * @shell: estrutura principal do shell
 * @t_lst: lista de tokens
 * 
 * Extrai todas as palavras que serão argumentos do comando,
 * ignorando redirecionamentos e seus alvos.
 * 
 * Return: array de strings terminado em NULL
 */
char	**get_argv(t_shell *shell, t_list *t_lst)
{
	int		argc;
	char	**argv;
	int		i;

	argc = 0;
	i = 0;
	argc = count_args(t_lst);
	
	argv = ft_calloc((argc + 1), sizeof(char *));
	if (!argv)
		exit_failure(shell, "get_argv");
	
	while (t_lst && ((t_token *)t_lst->content)->type != PIPE && i < argc)
	{
		if (!check_token(t_lst))
			break ;
		
		if (t_lst && ((t_token *)t_lst->content)->type == WORD)
		{
			t_lst = check_word(&t_lst, argv, &i);
			continue ;
		}
		
		if (!check_token(t_lst->next))
			break ;
		
		t_lst = t_lst->next->next; // Pula redirecionamento + seu alvo
	}
	
	argv[argc] = NULL;
	return (argv);
}

/**
 * get_infiles - Extrai todos os redirecionamentos de entrada
 * @shell: estrutura principal do shell
 * @tkn_lst: lista de tokens
 * @infiles: ponteiro para lista de infiles
 * 
 * Processa < e << criando estruturas apropriadas
 * 
 * Return: último token processado
 */
t_list	*get_infiles(t_shell *shell, t_list *tkn_lst, t_list **infiles)
{
	t_inf	*content;

	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
		{
			content = ft_calloc(sizeof(t_inf), 1);
			if (!content)
				exit_failure(shell, "get_infiles");
			
			// Define tipo de entrada
			if (((t_token *)tkn_lst->content)->type == INFILE)
				content->type = INF;
			else
				content->type = HERE;
			
			// Copia o delimitador/nome do arquivo
			content->eof = ft_strdup(((t_token *)
						tkn_lst->next->content)->value);
			
			ft_lstadd_back(infiles, ft_lstnew(content));
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		tkn_lst = tkn_lst->next;
		if (!check_token(tkn_lst))
			break ;
	}
	return (tkn_lst);
}

/**
 * get_outfiles - Extrai todos os redirecionamentos de saída
 * @shell: estrutura principal do shell
 * @tkn_lst: lista de tokens
 * @outfiles: ponteiro para lista de outfiles
 * 
 * Processa > e >> criando estruturas apropriadas
 * 
 * Return: último token processado
 */
t_list	*get_outfiles(t_shell *shell, t_list *tkn_lst, t_list **outfiles)
{
	t_outf	*content;

	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			content = ft_calloc(1, sizeof(t_outf));
			if (!content)
				exit_failure(shell, "get_outfiles");
			
			// Define tipo de saída
			if (((t_token *)tkn_lst->content)->type == APPEND)
				content->type = APP;
			else
				content->type = ADD;
			
			// Copia nome do arquivo
			content->name = ft_strdup(((t_token *)
						tkn_lst->next->content)->value);
			
			ft_lstadd_back(outfiles, ft_lstnew(content));
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		tkn_lst = tkn_lst->next;
		if (!check_token(tkn_lst))
			break ;
	}
	return (tkn_lst);
}

/**
 * get_colors - Adiciona flag --color=auto para ls e grep
 * @shell: estrutura principal do shell
 * @argv: array de argumentos original
 * 
 * Melhora a experiência do usuário adicionando cores
 * automaticamente para comandos visuais.
 * 
 * Return: novo array com flag de cor
 */
char	**get_colors(t_shell *shell, char **argv)
{
	char	**colors;
	int		i;
	int		j;

	i = 0;
	j = 1;
	
	// Conta argumentos
	while (argv[i])
		i++;
	
	colors = malloc(sizeof(char *) * (i + 2));
	if (!colors)
		exit_failure(shell, "get_colors");
	
	// Copia comando original
	colors[0] = argv[0];
	colors[1] = "--color=auto";
	
	// Copia argumentos restantes
	while (j < i)
	{
		colors[j + 1] = argv[j];
		j++;
	}
	colors[i + 1] = NULL;
	
	free(argv);
	return (colors);
}

/**
 * count_args - Conta quantos argumentos o comando tem
 * @tkn_lst: lista de tokens
 * 
 * Percorre tokens contando apenas palavras que serão argumentos,
 * ignorando redirecionamentos.
 * 
 * Return: número de argumentos
 */
int	count_args(t_list *tkn_lst)
{
	int		args;

	args = 0;
	while (tkn_lst && ((t_token *)tkn_lst->content)->type != PIPE)
	{
		// Pula redirecionamentos de entrada
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == INFILE
				|| ((t_token *)tkn_lst->content)->type == HEREDOC))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		// Pula redirecionamentos de saída
		if (tkn_lst && (((t_token *)tkn_lst->content)->type == OUTFILE
				|| ((t_token *)tkn_lst->content)->type == APPEND))
		{
			tkn_lst = tkn_lst->next->next;
			continue ;
		}
		
		tkn_lst = check_w_args(tkn_lst, &args);
		if (!check_token(tkn_lst))
			break ;
	}
	return (args);
}
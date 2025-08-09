/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:38:47 by luarodri          #+#    #+#             */
/*   Updated: 2025/08/08 19:18:56 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * skip_if - Pula tokens até encontrar PIPE ou operador lógico
 * @tmp: token atual
 * 
 * Usado para navegar pela lista quando não estamos em pipe
 * 
 * Return: próximo token relevante
 */
t_list	*skip_if(t_list *tmp)
{
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_token(tmp))
			break ;
	}
	return (tmp);
}

/**
 * skip_else - Pula token atual e continua até PIPE ou operador
 * @tmp: token atual
 * 
 * Usado quando estamos processando um pipe
 * 
 * Return: próximo token relevante
 */
t_list	*skip_else(t_list *tmp)
{
	tmp = tmp->next;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		tmp = tmp->next;
		if (!check_token(tmp))
			break ;
	}
	return (tmp);
}

/**
 * check_word - Processa token de palavra para argv
 * @current: token atual (passado por referência)
 * @argv: array de argumentos
 * @i: índice atual no array
 * 
 * Lida com tokens expandidos vazios que devem ser ignorados
 * 
 * Return: próximo token
 */
t_list	*check_word(t_list **current, char **argv, int *i)
{
	// Ignora tokens expandidos vazios
	if (*current && ((t_token *)(*current)->content)->state == EXPAND
		&& ft_strlen(((t_token *)(*current)->content)->value) == 0)
	{
		*current = (*current)->next;
		return (*current);
	}
	
	// Adiciona palavra ao argv
	argv[*i] = ((t_token *)(*current)->content)->value;
	*current = (*current)->next;
	(*i)++;
	return (*current);
}

/**
 * check_w_args - Conta argumentos ignorando tokens vazios
 * @tkn_lst: lista de tokens
 * @args: contador de argumentos
 * 
 * Usado por count_args para contar corretamente
 * 
 * Return: próximo token
 */
t_list	*check_w_args(t_list *tkn_lst, int *args)
{
	if (tkn_lst && ((t_token *)tkn_lst->content)->type == WORD)
	{
		// Ignora tokens expandidos vazios
		if (((t_token *)tkn_lst->content)->state == EXPAND
			&& ft_strlen(((t_token *)tkn_lst->content)->value) == 0)
		{
			return (tkn_lst->next);
		}
		(*args)++;
	}
	return (tkn_lst->next);
}

/**
 * check_token - Verifica se token é válido para processamento
 * @node: nó da lista
 * 
 * Função auxiliar para verificar se devemos continuar processando
 * 
 * Return: true se token é válido
 */
int	check_token(t_list *node)
{
	return (node && (((t_token *)node->content)->type != AND_IF
			&& ((t_token *)node->content)->type != OR));
}
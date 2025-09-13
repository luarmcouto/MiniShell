/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarmcouto <luarmcouto@student.42porto.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:00:00 by luarmcouto        #+#    #+#             */
/*   Updated: 2025/08/09 12:00:00 by luarmcouto       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * ARQUIVO TEMPORÁRIO - STUBS REDUZIDOS
 * 
 * Este arquivo contém apenas implementações temporárias de funções que 
 * ainda não foram implementadas. Funções como , exit_status,
 * free_env_lst, free_shell, etc. já existem no projeto.
 * 
 * À medida que implementamos os outros módulos (expansão, redirecionamentos,
 * etc.), estas funções serão movidas para seus arquivos apropriados.
 */

/**
 * execute_processes - Stub usando execute_tree diretamente
 * Por enquanto, chama execute_tree diretamente para evitar recursão
 */
void	execute_processes(t_shell *shell, void *root)
{
	// Por enquanto, executa a árvore diretamente sem as funcionalidades
	// extras como sinais e heredoc
	exec_tree(shell, root);
}

/**
 * check_files_order - Stub para processamento de redirecionamentos
 * TODO: Implementar no módulo de redirecionamentos
 */
void	check_files_order(t_shell *shell, t_exec *exec_node)
{
	(void)shell;
	(void)exec_node;
	// Por enquanto, não processa redirecionamentos
}

/**
 * check_wildcards - Stub para processamento de wildcards
 * TODO: Implementar no módulo de wildcards (bonus)
 */
void	check_wildcards(t_shell *shell, t_exec *exec_node)
{
	(void)shell;
	(void)exec_node;
	// Por enquanto, não processa wildcards
}

/**
 * handle_heredoc - Stub para processamento de heredoc
 * TODO: Implementar no módulo de heredoc
 */
void	handle_heredoc(t_shell *shell, void *root)
{
	(void)shell;
	(void)root;
	// Por enquanto, não processa heredoc
}

/**
 * is_directory - Implementação usando função existente de errors
 * A função is_directory já existe em exit_messages.c, mas com assinatura diferente.
 * Vamos fazer um wrapper para manter compatibilidade.
 */
void	is_directory(t_shell *shell, char **argv)
{
	// A função original retorna int e recebe char **path
	// Aqui fazemos um wrapper para manter compatibilidade
	(void)shell;
	(void)argv;
	// TODO: Integrar com função existente quando necessário
}
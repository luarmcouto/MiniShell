/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:37:44 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 19:20:35 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: diminuir número de funções.

#include <minishell.h>

/**
 * exit_code - Gestão global do código de saída
 * @value: novo valor do código de saída
 * 
 * Usa variável estática para manter o último código de saída
 * Se value == -1, retorna valor atual sem modificar
 * Caso contrário, atualiza e retorna novo valor
 * 
 * Return: código de saída atual
 */
int	exit_code(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	
	code = value;
	return (code);
}

/**
 * last_process - Gestão do código do último processo
 * @value: novo valor do código
 * 
 * Similar a exit_code, mas especificamente para
 * rastrear o último processo executado
 * Usado em operadores lógicos && e ||
 * 
 * Return: código do último processo
 */
int	last_process(int value)
{
	static int	code = 0;

	if (value == -1)
		return (code);
	
	code = value;
	return (code);
}

/**
 * exit_status - Processa status de processo filho
 * @status: status retornado por wait/waitpid
 * 
 * Converte status de processo para código de saída apropriado:
 * - Se terminou normalmente: usa código de saída
 * - Se terminou por sinal: 128 + número do sinal
 * 
 * Atualiza exit_code global automaticamente
 */
void	exit_status(int status)
{
	if (WIFEXITED(status))
	{
		// Processo terminou normalmente
		exit_code(WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		// Processo terminou por sinal (ex: Ctrl+C = SIGINT = 2)
		// Bash usa convenção: 128 + signal_number
		exit_code(128 + WTERMSIG(status));
	}
	
	// Atualiza também last_process para consistência
	last_process(exit_code(-1));
}

/**
 * itoa_exit - Converte exit code para string
 * @shell: estrutura principal do shell
 * @str: ponteiro para string resultado
 * 
 * Função específica para expansão de $?
 * Adiciona código de saída atual à string
 * 
 * Return: string atualizada
 */
char	*itoa_exit(t_shell *shell, char **str)
{
	char	*code_str;
	char	*tmp;

	code_str = ft_itoa(exit_code(-1));
	if (!code_str)
		exit_failure(shell, "itoa_exit");
	
	tmp = *str;
	*str = ft_strjoin(*str, code_str);
	free(tmp);
	free(code_str);
	
	if (!*str)
		exit_failure(shell, "itoa_exit_join");
	
	return (*str);
}

/**
 * set_exit_code_success - Define código de sucesso
 * 
 * Função utilitária para definir código 0 (sucesso)
 * Usada após comandos que executam com sucesso
 */
void	set_exit_code_success(void)
{
	exit_code(0);
}

/**
 * set_exit_code_error - Define código de erro genérico
 * 
 * Função utilitária para definir código 1 (erro genérico)
 * Usada para erros de sintaxe, argumentos inválidos, etc.
 */
void	set_exit_code_error(void)
{
	exit_code(1);
}

/**
 * set_exit_code_command_not_found - Comando não encontrado
 * 
 * Define código 127 (comando não encontrado)
 * Usado quando comando não existe no PATH
 */
void	set_exit_code_command_not_found(void)
{
	exit_code(127);
}

/**
 * set_exit_code_permission_denied - Permissão negada
 * 
 * Define código 126 (não pode executar)
 * Usado quando comando existe mas não tem permissão de execução
 */
void	set_exit_code_permission_denied(void)
{
	exit_code(126);
}

/**
 * set_exit_code_syntax_error - Erro de sintaxe
 * 
 * Define código 2 (erro de sintaxe)
 * Usado para erros de parsing, aspas não fechadas, etc.
 */
void	set_exit_code_syntax_error(void)
{
	exit_code(2);
}

/**
 * set_exit_code_signal - Código para término por sinal
 * @signal_num: número do sinal recebido
 * 
 * Define código 128 + signal_num conforme convenção bash
 * Usado quando processo é terminado por sinal
 */
void	set_exit_code_signal(int signal_num)
{
	exit_code(128 + signal_num);
}

/**
 * is_exit_success - Verifica se último código foi sucesso
 * 
 * Return: true se código == 0, false caso contrário
 */
bool	is_exit_success(void)
{
	return (exit_code(-1) == 0);
}

/**
 * is_exit_error - Verifica se último código foi erro
 * 
 * Return: true se código != 0, false caso contrário
 */
bool	is_exit_error(void)
{
	return (exit_code(-1) != 0);
}

/**
 * get_exit_code_string - Retorna código como string
 * @shell: estrutura principal do shell
 * 
 * Retorna código de saída atual como string alocada
 * Usada para expansão $? e debug
 * 
 * Return: string com código ou NULL se erro
 */
char	*get_exit_code_string(t_shell *shell)
{
	char	*code_str;

	code_str = ft_itoa(exit_code(-1));
	if (!code_str)
		exit_failure(shell, "get_exit_code_string");
	
	return (code_str);
}

/**
 * reset_exit_code - Reseta código para 0
 * 
 * Função utilitária para limpar estado
 * Usada no início de nova sessão ou após reset
 */
void	reset_exit_code(void)
{
	exit_code(0);
	last_process(0);
}

/**
 * handle_ctrl_c_exit_code - Código para Ctrl+C
 * 
 * Define código 130 (SIGINT = 2, então 128 + 2 = 130)
 * Usado quando usuário pressiona Ctrl+C
 */
void	handle_ctrl_c_exit_code(void)
{
	exit_code(130);
}

void	exit_failure(t_shell *shell, char *function)
{
	free_env_lst(shell->envp);
	free_shell(shell);
	ft_putstr_fd(RED"malloc error: "DEFAULT, 2);
	ft_putendl_fd(function, 2);
	exit(1);
}
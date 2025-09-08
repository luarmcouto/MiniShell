/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:23:20 by luarodri          #+#    #+#             */
/*   Updated: 2025/07/26 20:11:44 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_input(t_shell *shell)
{
	char	*prompt;
	char	*cwd;
	char	*tmp;
	char	*tmp2;
	char	*code;  // ← NOVA VARIÁVEL

	code = ft_itoa(exit_code(-1));  // ← NOVA LINHA
	cwd = getcwd(NULL, 0);
	prompt = ESC_START PROMPT ESC_RESET;
	tmp = ft_strjoin(prompt, code);  // ← MUDANÇA AQUI
	free(code);  // ← NOVA LINHA
	if (!tmp)
		exit_failure(shell, "shell_input");
	tmp2 = ft_strjoin(tmp, ESC_CODE);
	free(tmp);
	if (!tmp2)
		exit_failure(shell, "shell_input");
	tmp = ft_strjoin(tmp2, cwd);
	free(tmp2);
	if (!tmp)
		exit_failure(shell, "shell_input");
	shell->cwd = ft_strjoin(tmp, ARROW);
	free(cwd);
	free(tmp);
}


void	reset_shell(t_shell *shell)
{
	shell->envp_arr = NULL;
	shell->path = NULL;
	shell->token_lst = NULL;
	shell->input = NULL;
	shell->trim_input = NULL;
	shell->root = NULL;
	shell->cmd_path = NULL;
	shell->cwd = NULL;
	shell->exit_code = 0;
}

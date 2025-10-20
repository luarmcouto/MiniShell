/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:19:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/10/20 13:35:31 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_trim_args(char **args, int arg_idx)
{
	char	*trimmed;
	char	*temp;
	int		j;

	j = 0;
	while (j < arg_idx)
	{
		trimmed = ft_strtrim(args[j], ' ');
		temp = ft_strtrim(trimmed, '\t');
		free(trimmed);
		free(args[j]);
		args[j] = temp;
		j++;
	}
}

char	**ft_split_input(const char *input, int argc)
{
	char		**args;
	t_split_ctx	ctx;

	args = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!args)
		return (NULL);
	ft_init_split_ctx(&ctx);
	while (input[ctx.i] && ctx.arg_idx < argc)
	{
		ft_skip_whitespace(input, &ctx.i);
		if (!input[ctx.i])
			break ;
		if (ft_handle_operator(input, &ctx, args))
			continue ;
		ft_handle_word(input, &ctx, args);
	}
	args[ctx.arg_idx] = NULL;
	ft_trim_args(args, ctx.arg_idx);
	return (args);
}

void	ft_init_split_ctx(t_split_ctx *ctx)
{
	ctx->i = 0;
	ctx->arg_idx = 0;
	ctx->in_quote = 0;
	ctx->quote_char = 0;
}

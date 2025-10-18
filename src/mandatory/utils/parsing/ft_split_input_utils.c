/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:19:33 by luarodri          #+#    #+#             */
/*   Updated: 2025/09/17 20:19:41 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_handle_double_op(const char *input, t_split_ctx *ctx,
		char **args)
{
	if ((input[ctx->i] == '<' || input[ctx->i] == '>')
		&& input[ctx->i + 1] == input[ctx->i] && !ctx->in_quote
		&& !is_escaped(input, ctx->i, ctx->in_quote, ctx->quote_char))
	{
		args[ctx->arg_idx++] = ft_substr((char *)input, ctx->i, 2);
		ctx->i += 2;
		ft_skip_whitespace(input, &ctx->i);
		return (1);
	}
	return (0);
}

static int	ft_handle_single_redir(const char *input, t_split_ctx *ctx,
		char **args)
{
	if ((input[ctx->i] == '<' || input[ctx->i] == '>') && !ctx->in_quote
		&& !is_escaped(input, ctx->i, ctx->in_quote, ctx->quote_char))
	{
		args[ctx->arg_idx++] = ft_substr((char *)input, ctx->i, 1);
		ctx->i++;
		ft_skip_whitespace(input, &ctx->i);
		return (1);
	}
	return (0);
}

int	ft_handle_operator(const char *input, t_split_ctx *ctx, char **args)
{
	if (ft_handle_double_op(input, ctx, args))
		return (1);
	if (ft_handle_single_redir(input, ctx, args))
		return (1);
	if (input[ctx->i] == '|' && !ctx->in_quote
		&& !is_escaped(input, ctx->i, ctx->in_quote, ctx->quote_char))
	{
		args[ctx->arg_idx++] = ft_substr((char *)input, ctx->i, 1);
		ctx->i++;
		ft_skip_whitespace(input, &ctx->i);
		return (1);
	}
	return (0);
}

static void	ft_update_quote_state(const char *input, t_split_ctx *ctx)
{
	if (!ctx->in_quote && (input[ctx->i] == '\'' || input[ctx->i] == '"'))
	{
		ctx->in_quote = 1;
		ctx->quote_char = input[ctx->i];
		ctx->i++;
	}
	else if (ctx->in_quote && input[ctx->i] == ctx->quote_char)
	{
		ctx->in_quote = 0;
		ctx->quote_char = 0;
		ctx->i++;
	}
	else if (input[ctx->i] == '\\' && input[ctx->i + 1])
		ctx->i += 2;
	else
		ctx->i++;
}

void	ft_handle_word(const char *input, t_split_ctx *ctx, char **args)
{
	int	start;

	start = ctx->i;
	while (input[ctx->i])
	{
		if (!ctx->in_quote && (input[ctx->i] == '<' || input[ctx->i] == '>'
				|| input[ctx->i] == '|')
			&& !is_escaped(input, ctx->i, ctx->in_quote, ctx->quote_char))
			break ;
		if (!ctx->in_quote && ft_isspace(input[ctx->i]))
			break ;
		ft_update_quote_state(input, ctx);
	}
	if (ctx->i > start)
		args[ctx->arg_idx++] = ft_substr((char *)input, start, ctx->i - start);
}

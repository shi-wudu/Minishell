/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 07:32:20 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aplica a expansão de um único segmento
// SINGLE_QUOTED: literal, sem expansão
// DOUBLE/UNQUOTED: expande variáveis
// UNQUOTED pode gerar word splitting (IFS)

static void	apply_segment(t_segment *seg, t_expand_ctx *ctx)
{
	char	*expanded;

	if (seg->type == SINGLE_QUOTED)
	{
		*ctx->current = ft_strjoin_free(*ctx->current, seg->value);
		return ;
	}
	expanded = expand_vars(seg->value, ctx->data);
	if (seg->type == UNQUOTED)
		handle_unquoted(expanded, ctx->result, ctx->current, ctx->prev);
	else
		*ctx->current = ft_strjoin_free(*ctx->current, expanded);
	free(expanded);
}

static char	**expand_word_token(t_token *tok, t_data *data)
{
	t_segment		*seg;
	char			*current;
	char			**result;
	t_expand_ctx	ctx;

	seg = tok->segments;
	current = ft_strdup("");
	result = NULL;
	ctx.data = data;
	ctx.prev = UNQUOTED;
	ctx.current = &current;
	ctx.result = &result;
	while (seg)
	{
		apply_segment(seg, &ctx);
		ctx.prev = seg->type;
		seg = seg->next;
	}
	return (append_str_array(result, current));
}

// Percorre a lista de tokens

void	expand_tokens(t_token *tokens, t_data *data)
{
	while (tokens)
	{
		if (tokens->type == WORD)
			tokens->expanded = expand_word_token(tokens, data);
		tokens = tokens->next;
	}
}

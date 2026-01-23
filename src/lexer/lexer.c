/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2025/12/20 00:47:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Tokeniza a linha de input em uma lista ligada de tokens.

static t_token	*ft_tokenization_handler(char *line)
{
	t_token	*tokens;

	tokens = NULL;
	while (*line)
	{
		if (ft_is_space(*line))
			ft_skip_spaces(&line);
		else if (*line == '<' || *line == '>' || *line == '|')
		{
			if (!ft_handle_separator(&line, &tokens))
				return (ft_clear_token_list(&tokens), NULL);
		}
		else
		{
			if (!ft_append_identifier(&line, &tokens))
				return (ft_clear_token_list(&tokens), NULL);
		}
	}
	ft_token_list_add_back(&tokens, ft_new_token(END));
	return (tokens);
}

// Função principal do lexer.
// Cria tokens e valida a sintaxe.

bool	lexer(t_data *data)
{
	if (!data->user_input)
		return (false);
	data->token = ft_tokenization_handler(data->user_input);
	if (!data->token)
		return (false);
	if (!check_syntax(data->token))
	{
		ft_clear_token_list(&data->token);
		data->token = NULL;
		return (false);
	}
	return (true);
}

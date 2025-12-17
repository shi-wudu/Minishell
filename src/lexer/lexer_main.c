/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:14:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:52:49 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_token(t_token **tokens, const char *input, int i)
{
	if (input[i] == '\'' || input[i] == '"')
		return (handle_quote_case(tokens, input, i));
	if (is_redirect(input[i]))
		return (handle_redirects(tokens, input, i));
	if (input[i] == '|')
	{
		add_token(tokens, "|", PIPE);
		return (i + 1);
	}
	return (extract_word(tokens, input, i));
}

static t_token	*tokenize(const char *input)
{
	int		i;
	t_token	*tokens;
	int		next;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		next = handle_token(&tokens, input, i);
		if (next == -1)
			return (NULL);
		i = next;
	}
	add_token(&tokens, "END", END);
	return (tokens);
}

bool	lexer(t_data *data)
{
	if (!data->user_input || ft_strcmp(data->user_input, "") == 0)
		return (false);
	data->token = tokenize(data->user_input);
	if (!data->token)
		return (false);
	if (has_syntax_error(data->token))
	{
		free_tokens(data->token);
		data->token = NULL;
		return (false);
	}
	return (true);
}

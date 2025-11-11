/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
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

t_token	*tokenize(const char *input)
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

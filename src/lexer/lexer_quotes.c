/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:41 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:28:25 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_quoted(t_token **tokens, const char *input, int start)
{
	char	quote;
	int		i;
	char	*str;
	t_token_type	type;

	quote = input[start];
	i = start + 1;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		errmsg("minishell", "unclosed quote", true);
		return (-1);
	}
	str = ft_strndup(input + start + 1, i - start - 1);
	if (!str)
		return (-1);
	if (quote == '\'')
		type = STRING_SQUOTE;
	else
		type = STRING_DQUOTE;

	add_token(tokens, str, type);
	free(str);
	return (i + 1);
}


int	handle_quote_case(t_token **tokens, const char *input, int i)
{
	int	next;

	next = extract_quoted(tokens, input, i);
	if (next == -1)
	{
		free_tokens(*tokens);
		return (-1);
	}
	return (next);
}

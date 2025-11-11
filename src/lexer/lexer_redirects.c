/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:36 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:36 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirects(t_token **tokens, const char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (add_token(tokens, ">>", APPEND), i + 2);
	else if (input[i] == '>')
		return (add_token(tokens, ">", TRUNC), i + 1);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (add_token(tokens, "<<", HEREDOC), i + 2);
	else if (input[i] == '<')
		return (add_token(tokens, "<", INPUT), i + 1);
	return (i + 1);
}

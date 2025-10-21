/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:28:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extract_word(t_token **tokens, const char *input, int start)
{
	int		i;
	char	*str;

	i = start;
	while (input[i] && !ft_is_space(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
		i++;
	str = ft_strndup(input + start, i - start);
	if (!str)
		return (i);
	add_token(tokens, str, WORD);
	free(str);
	return (i);
}

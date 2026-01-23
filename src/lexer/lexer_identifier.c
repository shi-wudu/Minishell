/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/16 13:06:45 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word_char(char c)
{
	return (!ft_is_space(c) && c != '<' && c != '>' && c != '|');
}

// Cria um token WORD a partir da linha de input.

int ft_append_identifier(char **line, t_token **tokens)
{
    t_token     *tok;
    t_segment   *segs;
    size_t      i;

    segs = NULL;
    i = 0;
    while ((*line)[i] && is_word_char((*line)[i]))
    {
        if (parse_segment(*line, &i, &segs) == -1)
        {
            free_segments(segs);
            return (0);
        }
    }
    tok = ft_new_token(WORD);
    if (!tok)
        return (free_segments(segs), 0);
    tok->segments = segs;
    ft_token_list_add_back(tokens, tok);
    *line += i;
    return (1);
}

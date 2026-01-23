/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 07:03:57 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Determina o tipo de separador (<, >, >>, <<, |).

static t_token_type	get_separator_type(char *s)
{
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (APPEND);
	if (*s == '<')
		return (INPUT);
	if (*s == '>')
		return (TRUNC);
	if (*s == '|')
		return (PIPE);
	return (END);
}

// Trata operadores especiais e cria tokens de separadores.

int	ft_handle_separator(char **line, t_token **tokens)
{
	t_token_type	type;

	type = get_separator_type(*line);
	ft_token_list_add_back(tokens, ft_new_token(type));
	(*line)++;
	if (type == HEREDOC || type == APPEND)
		(*line)++;
	return (1);
}

// Cria um token WORD a partir da linha de input.

int	ft_append_identifier(char **line, t_token **tokens)
{
	t_token		*tok;
	t_segment	*segs;
	size_t		i;

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

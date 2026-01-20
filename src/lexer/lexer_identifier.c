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

static bool	is_word_char(char c)
{
	return (!ft_is_space(c) && c != '<' && c != '>' && c != '|');
}

// Salta conteúdo entre aspas, validando fecho correto.

static int	skip_quoted(char *s, size_t *i, size_t *len)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
	{
		(*len)++;
		(*i)++;
	}
	if (!s[*i])
		return (ft_print_quote_err(quote), -1);
	(*i)++;
	return (0);
}

// Calcula o comprimento de uma palavra considerando quotes.

static int	calc_word_len(char *s, size_t *len, bool *quoted)
{
	size_t	i;

	i = 0;
	*len = 0;
	*quoted = false;
	while (s[i] && is_word_char(s[i]))
	{
		if (ft_is_quote(s[i]))
		{
			*quoted = true;
			if (skip_quoted(s, &i, len) == -1)
				return (-1);
		}
		else
		{
			(*len)++;
			i++;
		}
	}
	return (i);
}

// Copia o conteúdo de uma palavra

static void	copy_word(char *dst, char *s, size_t stop)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < stop)
		dst[j++] = s[i++];
}

// Cria um token WORD a partir da linha de input.

int	ft_append_identifier(char **line, t_token **tokens)
{
	char	*word;
	size_t	len;
	int		consumed;
	bool	quoted;
	t_token	*tok;

	consumed = calc_word_len(*line, &len, &quoted);
	if (consumed < 0)
		return (0);
	word = ft_calloc(consumed + 1, sizeof(char));
	if (!word)
		return (0);
	copy_word(word, *line, consumed);
	tok = ft_new_token(word, WORD);
	if (!tok)
		return (free(word), 0);
	tok->quoted = quoted;
	ft_token_list_add_back(tokens, tok);
	*line += consumed;
	return (1);
}

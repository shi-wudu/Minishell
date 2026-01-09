/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2025/12/20 00:47:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_word_char(char c)
{
	return (!ft_is_space(c) && c != '<' && c != '>' && c != '|');
}

// Salta conteúdo entre aspas, validando fecho correto.

static int	skip_quoted(char *s, size_t *i, size_t *len, bool *no_expand)
{
	char	quote;

	quote = s[*i];
	if (quote == '\'')
		*no_expand = true;
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
// Marca se há single quotes (no_expand = true)

static int	calc_word_len(char *s, size_t *len, bool *no_expand)
{
	size_t	i;

	i = 0;
	*len = 0;
	*no_expand = false;
	while (s[i] && is_word_char(s[i]))
	{
		if (ft_is_quote(s[i]))
		{
			if (skip_quoted(s, &i, len, no_expand) == -1)
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

// Copia o conteúdo de uma palavra removendo aspas.

static void	copy_word(char *dst, char *s, size_t stop)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	while (i < stop)
	{
		if (ft_is_quote(s[i]))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				dst[j++] = s[i++];
			i++;
		}
		else
			dst[j++] = s[i++];
	}
}

// Cria um token WORD a partir da linha de input.

int	ft_append_identifier(char **line, t_token **tokens)
{
	char	*word;
	size_t	len;
	int		consumed;
	bool	no_expand;
	t_token	*tok;

	consumed = calc_word_len(*line, &len, &no_expand);
	if (consumed < 0)
		return (0);
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (0);
	copy_word(word, *line, consumed);
	tok = ft_new_token(word, WORD);
	if (!tok)
		return (free(word), 0);
	tok->no_expand = no_expand;
	ft_token_list_add_back(tokens, tok);
	*line += consumed;
	return (1);
}

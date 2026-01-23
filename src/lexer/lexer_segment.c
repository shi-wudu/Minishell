/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 07:08:34 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 07:09:15 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*new_segment(char *value, t_seg_type type)
{
	t_segment	*seg;

	seg = ft_calloc(1, sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->value = value;
	seg->type = type;
	seg->next = NULL;
	return (seg);
}

void	segment_add_back(t_segment **lst, t_segment *new)
{
	t_segment	*cur;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	free_segments(t_segment *seg)
{
	t_segment	*tmp;

	while (seg)
	{
		tmp = seg->next;
		free(seg->value);
		free(seg);
		seg = tmp;
	}
}

static int	parse_word(char *s, size_t *i, t_segment **segs, t_seg_type type)
{
	size_t	start;
	char	quote;

	quote = 0;
	if (type != UNQUOTED)
	{
		quote = s[*i];
		(*i)++;
	}
	start = *i;
	while (s[*i] && ((quote && s[*i] != quote) || (!quote && is_word_char(s[*i])
				&& !ft_is_quote(s[*i]))))
		(*i)++;
	if (quote && !s[*i])
		return (ft_print_quote_err(quote), -1);
	segment_add_back(segs, new_segment(ft_substr(s, start, *i - start), type));
	if (quote)
		(*i)++;
	return (0);
}

int	parse_segment(char *s, size_t *i, t_segment **segs)
{
	if (s[*i] == '\'')
		return (parse_word(s, i, segs, SINGLE_QUOTED));
	if (s[*i] == '"')
		return (parse_word(s, i, segs, DOUBLE_QUOTED));
	return (parse_word(s, i, segs, UNQUOTED));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2025/12/20 00:47:37 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	ft_skip_spaces(char **line)
{
	while (**line && ft_is_space(**line))
		(*line)++;
}

void	ft_print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

int parse_segment(char *s, size_t *i, t_segment **segs)
{
    size_t start;

    if (s[*i] == '\'')
    {
        (*i)++;
        start = *i;
        while (s[*i] && s[*i] != '\'')
            (*i)++;
        if (!s[*i])
            return (ft_print_quote_err('\''), -1);
        segment_add_back(segs,
            new_segment(ft_substr(s, start, *i - start), SINGLE_QUOTED));
        (*i)++;
    }
    else if (s[*i] == '"')
    {
        (*i)++;
        start = *i;
        while (s[*i] && s[*i] != '"')
            (*i)++;
        if (!s[*i])
            return (ft_print_quote_err('"'), -1);
        segment_add_back(segs,
            new_segment(ft_substr(s, start, *i - start), DOUBLE_QUOTED));
        (*i)++;
    }
    else
    {
        start = *i;
        while (s[*i] && is_word_char(s[*i]) && !ft_is_quote(s[*i]))
            (*i)++;
        segment_add_back(segs,
            new_segment(ft_substr(s, start, *i - start), UNQUOTED));
    }
    return (0);
}

t_segment *new_segment(char *value, t_seg_type type)
{
    t_segment *seg;

    seg = ft_calloc(1, sizeof(t_segment));
    if (!seg)
        return (NULL);
    seg->value = value;
    seg->type = type;
    seg->next = NULL;
    return (seg);
}

void segment_add_back(t_segment **lst, t_segment *new)
{
    t_segment *cur;

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

void free_segments(t_segment *seg)
{
    t_segment *tmp;

    while (seg)
    {
        tmp = seg->next;
        free(seg->value);
        free(seg);
        seg = tmp;
    }
}
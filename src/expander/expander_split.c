/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 06:19:17 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 06:49:39 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// Divide uma string usando IFS (espaço, tab, newline)
// Ignora múltiplos separadores consecutivos

static char	**split_ifs(const char *s)
{
	char	**res;
	int		i;
	int		start;

	res = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_ifs(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !is_ifs(s[i]))
			i++;
		res = append_str_array(res, ft_substr(s, start, i - start));
	}
	return (res);
}

// Aplica word splitting (IFS) em texto UNQUOTED
// Pode transformar uma string em várias palavras
// Usa o tipo do segmento anterior para decidir junções

void	handle_unquoted(char *expanded, char ***result,
		char **current, t_seg_type prev)
{
	char	**split;
	int		i;

	split = split_ifs(expanded);
	i = 0;
	if (split && split[0])
	{
		if (prev != UNQUOTED)
		{
			*result = append_str_array(*result, *current);
			*current = ft_strdup(split[i++]);
		}
		else
			*current = ft_strjoin_free(*current, split[i++]);
		while (split[i])
		{
			*result = append_str_array(*result, *current);
			*current = ft_strdup(split[i++]);
		}
	}
	free_args(split);
}

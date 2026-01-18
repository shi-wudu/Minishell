/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/16 13:15:02 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Acrescenta um caractere a uma string, realocando-a.
char	*append_char(char *s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(s, tmp);
	if (!new)
	{
		free(s);
		return (NULL);
	}
	free(s);
	return (new);
}

void	handle_this(const char *str, int *i, char **res, t_data *data)
{
	int		start;
	char	*name;
	char	*val;

	if (str[*i + 1] == '{')
	{
		*i += 2;
		start = *i;
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (str[*i] != '}')
		{
			*res = ft_strjoin_free(*res, "${");
			return ;
		}
		name = ft_substr(str, start, *i - start);
		val = get_env_value(data->envp, name);
		if (val)
			*res = ft_strjoin_free(*res, val);
		free(name);
		(*i)++;
		return ;
	}
}

bool	handle_quote_char(const char *str, int *i, char *quote, char **res)
{
	char	c;

	c = str[*i];
	if (*quote == 0)
	{
		*quote = c;
		(*i)++;
		return (true);
	}
	if (*quote == c)
	{
		*quote = 0;
		(*i)++;
		return (true);
	}
	*res = append_char(*res, c);
	(*i)++;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
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
	free(s);
	return (new);
}

void handle_this(const char *str, int *i, char **res, t_data *data)
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
			return ;
		name = ft_substr(str, start, *i - start);
		val = get_env_value(data->envp, name);
		if (val)
			*res = ft_strjoin_free(*res, val);
		free(name);
		(*i)++;
		return ;
	}
}